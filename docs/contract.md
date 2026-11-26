# Serial contract

## Frame format

[Peripheral](../include/serial/peripheral.hpp) accepts a positive nominal bit rate and a configured width from 1 to 16. Implement the subset of [Config](../include/serial/types.hpp) supported by the target. Asynchronous framing needs one or two stop symbols. Synchronous links may use no stop symbols where supported, with clock role supplied by composition. A `Frame` stores its bits in the low portion of a 16-bit word. Values with bits above the configured width are invalid.

## Progress without a wait

`try_write` accepts one frame for transmission or reports `Busy`. `try_read` reports `Busy` when no frame can be read, and changes its output only on success. `FrameError` and `Overrun` describe receive faults. Discard a corrupt frame when reporting it. `transmission_complete` includes the queue and the final frame on the wire. The try operations take no timeout.

## Implementation boundary

The Adapter owns resource state. The caller must keep the implementation alive during each call and arrange access from other execution contexts. Document the contexts and concurrency guarantees of the actual implementation. Shared public types are in [`serial/types.hpp`](../include/serial/types.hpp).
