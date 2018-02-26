/**
 * CAN Controller Driver Interface
 *
 * Authors: Michael Rouse
 */
#ifndef __CAN_CONTROLLER_INTERFACE__
#define __CAN_CONTROLLER_INTERFACE__
#include "../datatypes.h"
#include "../utils/pubsub/interface.h"


/* Initializes the CAN Controller */
void can_controller_setup(spi_bus bus, io_pin cs_pin, io_pin int_pin, uint16_t filters[], uint16_t masks[]);

/* Transmits a message over the CAN Bus */
void can_controller_transmit(can_message* msg);

/* Checks for missed interrupts and will automatically put missed messages in the rx queue */
void can_controller_poll(void);



// PubSub Event
extern pubsub_event_id CAN_CONTROLLER_TRANSMITTING_EVENT;






/* CAN Controller Initialization (should not be called by user unless unit testing) */
void __can_controller_initialization(
  uint8_t(*spi_transmit_func)(spi_bus, uint8_t),
  void(*pin_set_mode_func)(io_pin, pin_mode),
  void(*pin_set_level_func)(io_pin, pin_level),
  pin_level(*_pin_read_func)(io_pin),
  void(*attach_interrupt_func)(io_pin, void(*func)(void)),
  void(*can_receive_push_func)(can_message*)
);
#endif