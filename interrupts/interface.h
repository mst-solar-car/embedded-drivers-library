/**
 * This is the interface for the interrupt drivers
 *
 * Authors: Michael Rouse
 */
#ifndef __INTERRUPTS_INTERFACE__
#define __INTERRUPTS_INTERFACE__
#include "../library.h"


/* Registers an event with on a pin */
void interrupt_attach(io_pin pin, void(*func)(void));

/* Dispatches an interrupt to the appropriate function if it exists */
void __interrupt_dispatch(uint8_t port);




/* Initialize the Interrupt Drivers */
void interrupts_initialization(
  uint8_t mc_get_interrupt_port_bit(uint8_t)
);

#endif