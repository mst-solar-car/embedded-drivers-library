# MCP2515 Configuration
The following configuration is supported by the [`MCP2515` drivers](mcp2515/):

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
|&nbsp;|&nbsp;|
|`MCP2515_RESET_PIN`|YES|Define this, and give the value of the pin that `RESET` is connected to.<br/>This will force the drivers to toggle this pin low instead of sending the `reset` SPI command|
|&nbsp;|&nbsp;|
|`MCP2515_NO_ROLLOVER`|NO|Define this value to disable allowing the receive buffers to rollover when new messages are received (*doing this is not recommended*)|
