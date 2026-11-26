# Porting the Serial Contract

Hardware Definitions can describe serial instances, clock roles, frame widths and buffering facilities. The Adapter reports the supported combinations and timing tolerance. The portable API covers both synchronous and asynchronous framed links. It does not standardize application buffering, hardware flow control or error recovery.

This repository's host simulations and shared API compile/link checks provide source-level evidence. Target timing and physical behavior require hardware validation.
