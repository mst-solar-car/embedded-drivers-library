/**
 * Header file for the SPI driver implementation
 *
 * Author: Michael Rouse
 */
#ifndef __SPI_H__
#define __SPI_H__

#include "../datatypes.h"
#include "../utils.h"
#include "../microcontrollers/importer.h" // Import the microcontroller


/**
 * Functions provided by the SPI library
 */

// Configures a SPI bus
void spi_setup(spi_bus bus, io_pin mosi, io_pin miso, io_pin sck);

// Sends data over the SPI bus
uint8_t spi_transmit(spi_bus bus, uint8_t data);

#endif
