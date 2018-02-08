/**
 * CAN Controller Driver Interface
 *
 * Authors: Michael Rouse
 */
#ifndef __CAN_CONTROLLER_INTERFACE__
#define __CAN_CONTROLLER_INTERFACE__
#include "../datatypes.h"


/* Initializes the CAN Controller */
void can_controller_setup(io_pin cs_pin, io_pin int_pin);

/* Transmits a message over the CAN Bus */
void can_controller_transmit(can_message* msg);

/* Checks for missed interrupts and will automatically put missed messages in the rx queue */
void can_controller_poll(void);











/* CAN Controller Initialization (should not be called by user unless unit testing) */
void can_controller_initialization(
  uint8_t(*spi_transmit_func)(spi_bus, void*, uint8_t),
  void(*pin_set_mode_func)(io_pin, pin_mode),
  void(*pin_set_level_func)(io_pin, pin_level),
  void(*attach_interrupt_func)(io_pin, void(*func)(void))
);
#endif