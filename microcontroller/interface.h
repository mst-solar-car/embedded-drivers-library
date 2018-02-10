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



/* Used by the Pin Control Driver for controlling pins */
void __microcontroller_set_pin_mode(io_pin pin, pin_mode mode);

/* Used by the Pin Control Driver for controlling pins */
void __microcontroller_set_pin_level(io_pin pin, pin_level level);

/* Used by the Pin Control Driver for controlling pins */
pin_level __microcontroller_read_pin(io_pin pin);

/* Configures a SPI Bus */
void __microcontroller_spi_setup(spi_bus bus, io_pin mosi, io_pin miso, io_pin sck);

/* Transmits data over a SPI bus */
uint8_t __microcontroller_spi_transmit(spi_bus bus, void* data, uint8_t size);




/* Determines what bit on the port an interrupt happened on */
uint8_t __microcontroller_get_interrupt_port_bit(uint8_t port);



/* This function is for initializing the Microcontroller drivers, it should be */
/* implemented with every driver for each microcontroller. It should do basic generic */
/* initialization such as pins and clocks. */
/* It should NOT be called by the user. */
void microcontroller_initialization(void);




#endif