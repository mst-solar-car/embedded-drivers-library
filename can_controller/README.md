# CAN Controller
The CAN Controller drivers do not expose any functions that a programmer might be interested in calling manually,
unless they need to manually access the CAN controller (i.e., go around the CAN drivers).

Each CAN Controller driver might implement things differently, and can also expose certain functions to the user. It is not advised to use these because it is hardware-dependent. And this is a last resort option.

&nbsp;

This table describes functions exposed by this drivers interface, and that is used inside the CAN Driver. All CAN Controller driver implementations must implement these:

| Syntax | Description |
|--------|-------------|
|`void can_controller_setup(spi_bus, cs_pin, int_pin, filters[], masks[])`|Configures a CAN Controller |
|`void can_controller_transmit(can_message*)`|Sends a CAN message |
|`void can_controller_poll()`| Checks for missed interrupts, and receives a message if there is one |


&nbsp;

# Registration
The [registration.h](registration.h) file is what determines which CAN Controller driver will be loaded. Look at that file for an example on how we select the MCP2515.