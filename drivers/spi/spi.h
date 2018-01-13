/**
 * Header file for the SPI driver implementation
 *
 * Author: Michael Rouse
 */
#ifndef __SPI_H__
#define __SPI_H__

#include "../datatypes.h"
#include "../microcontrollers/importer.h" // Import the microcontroller

void spi_setup(io_pin mosi, io_pin miso, io_pin sck);
uint8_t spi_transmit(uint8_t data);

#endif
