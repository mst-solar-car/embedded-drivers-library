# SPI Drivers
The SPI drivers are just a wrapper around the Microcontroller SPI functions (`microcontroller_spi_x()`).


&nbsp;

# Functions
The following functions are exposed by the SPI drivers:

| Syntax | Description |
|--------|--------------|
|`void spi_setup(bus_id, mosi, miso, sck)` | Configures a SPI bus with `bus_id`|
|`uint8_t spi_transmit(bus_id, data)`| Sends `data` over `bus_id` and returns what was read in response |

&nbsp;

# Configuration
The SPI drivers look for the following configuration options in the `user_config.h` file:

| Option | Needs Value? | Description |
|--------|--------------|-------------|
|`DEFAULT_SPI_BUS` | YES | The default SPI bus for the library to use |