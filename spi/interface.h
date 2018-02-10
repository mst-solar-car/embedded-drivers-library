/**
 * Interface for SPI Drivers.
 *
 * Authors: Everyone?
 */
#ifndef __SPI_INTERFACE__
#define __SPI_INTERFACE__
#include "../datatypes.h"
#include "../library.h"


/* Setups a specific SPI bus */
void spi_setup(spi_bus bus, io_pin mosi, io_pin miso, io_pin sck);

/* Sends data over a SPI bus, returns received data */
uint8_t spi_transmit(spi_bus bus, uint8_t data);






/* This function is for initializing the SPI drivers, and should not be called */
/* by the user unless in a unit test */
void spi_initialization(void(*spiSetup)(spi_bus, io_pin, io_pin, io_pin), uint8_t(*spiTransmit)(spi_bus, void*, uint8_t));


#endif