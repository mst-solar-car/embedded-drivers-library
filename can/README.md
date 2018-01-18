# CAN Drivers
The CAN Drivers are just a wrapper around [CAN Controller Drivers](../can_controllers/README.md).

The user should never directly interact with the CAN Controller, only the CAN Drivers.

&nbsp;

# Functions
The following functions are how the user interacts with CAN Drivers:

| Syntax | Description |
|--------|-------------|
|`void can_setup(cs_pin, int_pin)`| Setups up CAN, and the CAN Controller. Pass it the Chip Select pin and the Interrupt Pin |
|`can_message* can_receive()`| Returns a pointer to a CAN Message that was received |
|`bool can_transmit()`| Sends the current message across the CAN Bus |


&nbsp;

# Variables
The following variables are exposed by the CAN drivers and are available for the user:

| Name | Type | Description |
|------|------|-------------|
| `can_new_msg` | `can_message*` | Used for populating the message before calling `can_transmit()`|

&nbsp;

# Configuration
The following configuration options can be defined in the `user_config.h` file:

| Option | Needs Value? | Description |
|--------|--------------|-------------|
|`CAN_FILTER1`| YES | Filter for messages to receive |
|`CAN_FILTER2`| YES | Filter for messages to receive |
|`CAN_FILTER3`| YES | Filter for messages to receive |
|`CAN_FILTER4`| YES | Filter for messages to receive |
|`CAN_FILTER5`| YES | Filter for messages to receive |
|`CAN_FILTER6`| YES | Filter for messages to receive |
|&nbsp;|&nbsp;|
|`CAN_MASK1`| YES | Mask for checking message IDs against filters |
|`CAN_MASK2`| YES | Mask for checking message IDs against filters |


&nbsp;

# Examples
For examples of how to use CAN please see the [examples file](../EXAMPLES.md).