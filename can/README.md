# CAN Drivers
The CAN drivers are really nothing more than a wrapper around the [CAN Controller drivers](../can_controller/README.md).

When programming you should only interact with these drivers, not directly with the CAN Controller drivers, unless a special case is needed.

CAN drivers should be designed to be robust enough to support different CAN Controllers, if a new CAN Controller in the future
does not work properly with these CAN drivers then upgrade them with other CAN Controllers in mind.

&nbsp;

# Functions
The following functions are how you can interact with these CAN drivers:

| Syntax | Description |
|--------|-------------|
|`void can_accept(filter, filter, filter, mask)`| Use this to tell the CAN drivers what messages you want to accept.<br/>Only the first `filter` is mandatory, filters will default to `CAN_DEFAULT_FILTER` and `mask` will default to `CAN_DEFAULT_MASK`. |
|`void can_setup(spi_bus, cs_pin, int_pin)` | Call this after using `can_accept()`. It will initailize everything for the CAN drivers that is not already initialized. |
|`can_message* can_receive()`| Returns a pointer to the next received CAN message. `NO_MESSAGE` if nothing to receive |
|`void can_transmit()`|Call this after setting up `can_new_msg` to transmit the message|

These functions are defined and commented in [can/interface.h](interface.h).

&nbsp;

# Variables
The following variables are exposed by the CAN driver for the programmer:

| Variable | Type | Description |
|----------|------|-------------|
|`can_new_msg` | `can_message` | Use this to create a new CAN message before calling `can_transmit()`|


&nbsp;

# Constants
The following constants are defined by this library:

| Constant | Value |
|----------|-------|
|`CAN_DATA_LENGTH` | `8` |
|`CAN_DEFAULT_MASK` | `0x000` |
|`CAN_DEFAULT_FILTER` | `0x7FF` |


