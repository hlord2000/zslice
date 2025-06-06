zslice is an RPC protocol for serial devices. It implements reception of packets in correct order and makes registering handlers to specific packet types as easy as possible.

zslice uses nanopb for serialization and Zephyr's COBS + CRC (optionally) for packet framing and error checking. 

It is possible to use zslice with acks between two communicating devices. 

Any device that exposes a Zephyr serial API can be used.

Planned support:
UART
BLE (with NUS)
USB CDC-ACM
