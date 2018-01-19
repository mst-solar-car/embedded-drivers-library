# MSP430F5529 Drivers
The MSP430F5529 drivers are the original drivers that were implemented for this
library.

&nbsp;

# Pin Control

The table below represents how you can identify pins inside your program when using
the MSP430F5529 drivers:

| Name | Description |
|-----|-------------|
|`PIN1` - `PIN80`| Can be used to identify pins in program. |
|`Px_0` - `Px_7` | Used for pin control, this is `Px.0` - `Px.7`|

&nbsp;

# SPI Buses
The MSP430F5529 has 4 SPI buses: `UCA0`, `UCA1`, `UCB0`, and `UCB1`.

This table shows you how to use those SPI buses in your program (`spi_setup()`, and `spi_transmit()`):

| Variable | Actual SPI Bus |
|----------|----------------|
|`SPI_BUS_1` | `UCA0` |
|`SPI_BUS_2` | `UCA1` |
|`SPI_BUS_3` | `UCB0` |
|`SPI_BUS_4` | `UCB1` |


# Configuration
The MSP430F5529 drive requires **NO** configuration in the `user_config.h` file.