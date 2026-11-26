# Serial Contract guide

A successful transmit call accepts a frame. The link can still be transmitting when that call returns. Read frame format and progress semantics before designing a polling loop.

1. Start with [the contract](contract.md) for implementer obligations and capability boundaries.
2. Read [the conformance example](examples.md) for an implementation you can compile locally.
3. Consult [the portability notes](compatibility.md) before choosing a hardware mapping.