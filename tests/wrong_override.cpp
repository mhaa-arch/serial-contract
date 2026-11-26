#include <serial/peripheral.hpp>

using namespace mhaa::serial;

class WrongOverride final : public Peripheral
{
public:
    Status configure(const Config &config) const override;
};
