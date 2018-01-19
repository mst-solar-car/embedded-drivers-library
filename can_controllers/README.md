# CAN Controller Drivers
The CAN Controller Drivers are the main force behind the CAN Drivers.

It is what actually interacts with the CAN Bus, sending and receiving messages.

&nbsp;

| Driver Documentation |
|:------:|
|[MCP2515](mcp2515/README.md)|

&nbsp;

# About
The CAN Controller Drivers have an `importer.h` just like the Microcontroller Drivers.

The only difference is that you can not have the compiler autodetect which CAN Controller you are using, so either comment out the wrong CAN Controller drivers or add a directive to `user_config.h` which defines the CAN Controller to use.

&nbsp;

# Functions
The following functions are exposed by the CAN Controller drivers:

| Syntax | Description |
|--------|-------------|
| `void can_controller_setup(int_pin, cs_pin)` | This is called by the `can_setup` function and gets passed the same parameters. |
| `bool can_controller_transmit(can_message* msg)` | Transmits `msg` over the bus and returns `True` if the message was sent. `False` if it could not be sent. |
| `void can_controller_poll()` | This function will check for a missed interrupt. If interrupts are not supported then it is the only way to check for new messages. <br/><br/>This function is called inside the `can_receive()` and `can_transmit()` functions |


