# CAN Drivers
The CAN Drivers are just a wrapper around [CAN Controller Drivers](../can_controllers/README.md).

The user should never directly interact with the CAN Controller, only the CAN Drivers.

The following functions are how the user interacts with CAN Drivers:

| Syntax | Description |
|--------|-------------|
|`void can_setup(cs_pin, int_pin)`| Setups up CAN, and the CAN Controller. Pass it the Chip Select pin and the Interrupt Pin |
|`can_message* can_receive()`| Returns a pointer to a CAN Message that was received |
|`bool can_transmit(can_message* msg)`||