#ifndef MHAA_SERIAL_PERIPHERAL_HPP
#define MHAA_SERIAL_PERIPHERAL_HPP

#include <serial/types.hpp>

namespace mhaa
{
    namespace serial
    {
        /** @brief Moves one framed serial word at a time on a configured link. */
        class Peripheral
        {
        public:
            virtual ~Peripheral() = default;
            virtual Status configure(const Config &config) = 0;

            /** @brief Enqueues one frame without waiting for transmission. */
            virtual Status try_write(Frame frame) = 0;

            /** @brief Reads one frame without waiting. Assigns frame only on Success. */
            virtual Status try_read(Frame &frame) = 0;
            virtual bool transmission_complete() const = 0;
        };
    }
}

#endif
