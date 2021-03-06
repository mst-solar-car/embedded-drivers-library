/**
 * This file is the interface for all Microcontroller Drivers that may be implemented
 * in the future.
 *
 *
 * Authors: Michael Rouse
 */
#ifndef __MICROCONTROLLER_INTERFACE__
#define __MICROCONTROLLER_INTERFACE__

#include "../datatypes.h"



/* Configures a SPI Bus */
void __microcontroller_spi_setup(spi_bus bus, io_pin mosi, io_pin miso, io_pin sck);

/* Transmits data over a SPI bus */
uint8_t __microcontroller_spi_transmit(spi_bus bus, uint8_t data);

/* Enables or disables interrupts */
void __microcontroller_interrupts_configure(bool enable);


/* This function is for initializing the Microcontroller drivers, it should be */
/* implemented with every driver for each microcontroller. It should do basic generic */
/* initialization such as pins and clocks. */
/* It should NOT be called by the user. */
void __microcontroller_initialization(void);




#endif