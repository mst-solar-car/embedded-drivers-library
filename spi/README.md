# SPI Drivers
The SPI drivers are used to communicate with other ICs on a board, they directly
interface with the microcontroller drivers.

&nbsp;

# Functions
The following functions are exposed, for the user, by the SPI drivers:

| Syntax | Description |
|--------|-------------|
|`spi_setup(spi_bus, mosi_pin, miso_pin, sck_pin)` | This NEEDS to be called before calling anything that performs SPI operations. It will initialize the SPI bus with the microcontroller. |
|`uint8_t spi_transmit(spi_bus, data)` | This will transmit `data` over `spi_bus`, and return whatever data was received. |