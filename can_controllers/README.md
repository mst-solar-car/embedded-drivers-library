# CAN Controller Drivers
The CAN Controller Drivers are the main force behind the CAN Drivers.

It is what actually interacts with the CAN Bus, sending and receiving messages.

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



&nbsp;

# MCP2515 Configuration
The following configuration is supported by the (`MCP2515` drivers)[mcp2515/]:

| Option | Needs Value? | Description |
|--------|--------------|-------------|
|`MCP2515_USE_RTS_PINS`| NO | Define this if you want to use the `TX0RTS`, `TX1RTS`, and `TX2RTS` pins instead of sending a ready-to-send command over SPI (doing this is suggested) |
|`MCP2515_TX0RTS_PIN`| YES | Pin that `TX0RTS` is connected to |
|`MCP2515_TX1RTS_PIN`| YES | Pin that `TX1RTS` is connected to |
|`MCP2515_TX2RTS_PIN`| YES | Pin that `TX2RTS` is connected to |
|&nbsp;|&nbsp;|
|`MSP2515_USE_RXBF_PINS`|NO| Define this to use the `RX0BF` and `RX1BF` pins instead of the `INT` pin for interrupts |
|`MCP2515_RX0BF_PIN`|YES| Pin that `RX0BF` is connected to |
|`MCP2515_RX1BF_PIN`|YES| Pin that `RX1BF` is connected to |