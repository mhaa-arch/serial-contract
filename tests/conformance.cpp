#include <serial/peripheral.hpp>

#include <cassert>

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

int main()
{
    Fake fake(9);
    Peripheral &serial = fake;
    assert(serial.configure({9600, Mode::Asynchronous, 9, Parity::None, StopBits::One}) == Status::Success);
    assert(serial.try_write(0x185) == Status::Success);
    Frame value = 0;
    assert(serial.try_read(value) == Status::Success && value == 0x185);
    assert(serial.try_read(value) == Status::Busy && value == 0x185);
    assert(serial.transmission_complete());
}
