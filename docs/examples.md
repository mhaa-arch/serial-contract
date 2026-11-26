# Serial Contract example

[The conformance program](../tests/conformance.cpp) pairs a simulated implementation with assertions at the Contract boundary. The test configures a nine-bit asynchronous link, submits `0x185`, and reads the same value from the simulated loopback. A second poll returns `Busy` and preserves the last value. The fake reports transmission complete after draining its slot. A real Adapter must observe the wire-level completion guarantee.

## Implementation excerpt

This class is taken from the program. The linked source contains the test cases and any additional fixtures.

```cpp
#include <serial/peripheral.hpp>


using namespace mhaa::serial;

class Fake final : public Peripheral
{
public:
    explicit Fake(uint8_t width) : width_(width) {}

    Status configure(const Config &config) override
    {
        return config.data_bits == width_ ? Status::Success : Status::Unsupported;
    }

    Status try_write(Frame frame) override
    {
        if (available_)
        {
            return Status::Busy;
        }
        if (uint32_t{frame} >> width_)
        {
            return Status::InvalidArgument;
        }
        frame_ = frame;
        available_ = true;
        return Status::Success;
    }

    Status try_read(Frame &frame) override
    {
        if (!available_)
        {
            return Status::Busy;
        }
        frame = frame_;
        available_ = false;
        return Status::Success;
    }

    bool transmission_complete() const override { return !available_; }

private:
    uint8_t width_;
    Frame frame_ = 0;
    bool available_ = false;
};
```

## Build and run

From this repository root, with assertions enabled, compile the full program. A passing run exits with status 0 and prints no output. Use `conformance.exe` on Windows.

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude tests/conformance.cpp -o conformance
./conformance
```

To verify enforcement of the abstract interface, compile the two negative sources separately. The first should diagnose an abstract type and the second an incompatible override.

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude -fsyntax-only tests/missing_override.cpp
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude -fsyntax-only tests/wrong_override.cpp
```
