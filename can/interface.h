/**
 * CAN Driver Interface
 *
 * Authors: Michael Rouse
 */
#ifndef __CAN_INTERFACE__
#define __CAN_INTERFACE__
#include "../datatypes.h"



/* Used to configure CAN filters and Masks */
#define can_accept(...)   CAT(__can_accept_, NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)

/* Do not use this function unless you really want to, otherwise use can_accept() */
void __can_accept(
  uint16_t filter1, uint16_t filter2, uint16_t filter3,
  uint16_t mask
);


/* can_setup should be called by the user to setup the library and CAN Controller */
void can_setup(spi_bus bus, io_pin cs_pin, io_pin int_pin);

/* can_receive should be called when retrieving the most recent messages */
/* NO_MESSAGE is returned if no messages are available */
can_message* can_receive(void);

/* can_transmit should be called after populating a message and it's ready to send */
void can_transmit(void);




/* This variable should be used in the user's program to populate a message before */
/* calling can_transmit(). MUST call can_transmit() in-order for this variable */
/* to point to a brand new and empty CAN message */
extern can_message can_new_msg;



/* This function is for the CAN Controller to pass received messages to the CAN Drivers */
extern void __can_add_to_receive_queue(can_message* msg);


/* This function is for initializing the CAN drivers, and should not be called */
/* by the user unless in a unit test */
void __can_initialization(
  void(*can_setup_func)(spi_bus, io_pin, io_pin, uint16_t[], uint16_t[]),
  void(*can_poll_func)(void),
  void(*can_transmit_func)(can_message*)
);



/* Allows for an optional number of parameters on can_accept */
#define DEFAULT_CAN_FILTER    0x7FF
#define __can_accept_0()                                                                    /* Nothing */
#define __can_accept_1(filter1)                                                             __can_accept((uint16_t)filter1, 0x000, 0x000, DEFAULT_CAN_FILTER);
#define __can_accept_2(filter1, filter2)                                                    __can_accept((uint16_t)filter1, (uint16_t)filter2, 0x000, DEFAULT_CAN_FILTER)
#define __can_accept_3(filter1, filter2, filter3)                                           __can_accept((uint16_t)filter1, (uint16_t)filter2, (uint16_t)filter3, DEFAULT_CAN_FILTER)
#define __can_accept_4(filter1, filter2, filter3, mask)                                     __can_accept((uint16_t)filter1, (uint16_t)filter2, (uint16_t)filter3, (uint16_t)mask)

#define __can_accept_6(filter1, filter2, filter3, filter4, filter5, filter6)                __can_accept_3(filter1, filter2, filter3); __can_accept_3(filter4, filter5, filter6)
#define __can_accept_7(filter1, filter2, filter3, filter4, filter5, filter6, mask)          __can_accept_4(filter1, filter2, filter3, mask); __can_accept_4(filter4, filter5, filter6, mask)



#endif

