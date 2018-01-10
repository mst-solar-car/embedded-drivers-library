/**
 * SPI Driver Header File
 *
 * Author: Michael Rouse
 */
#ifndef __SOLARCAR_SPI_H__
#define __SOLARCAR_SPI_H__

#include "solarcar.h"

void spi_setup();

void spi_transmit(uint8_t data);

#endif