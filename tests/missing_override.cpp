#include <serial/peripheral.hpp>

using namespace mhaa::serial;

class Incomplete final : public Peripheral
{
public:
    Status try_write(Frame frame) override;
    Status try_read(Frame &frame) override;
    bool transmission_complete() const override;
};

int main()
{
    Incomplete implementation;
    (void)implementation;
}
