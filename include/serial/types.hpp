#ifndef MHAA_SERIAL_TYPES_HPP
#define MHAA_SERIAL_TYPES_HPP

#include <stdint.h>

namespace mhaa
{
    namespace serial
    {
        enum class Mode
        {
            Asynchronous,
            Synchronous
        };
        enum class Parity
        {
            None,
            Even,
            Odd
        };
        enum class StopBits
        {
            None = 0,
            One = 1,
            Two = 2
        };
        using Frame = uint16_t;

        struct Config
        {
            uint32_t baud_rate;
            Mode mode;
            uint8_t data_bits;
            Parity parity;
            StopBits stop_bits;
        };

        enum class Status
        {
            Success,
            Busy,
            InvalidArgument,
            Unsupported,
            FrameError,
            Overrun,
            Error
        };
    }
}

#endif
