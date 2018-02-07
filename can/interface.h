/**
 * CAN Driver Interface
 *
 * Authors: Michael Rouse
 */
#ifndef __CAN_INTERFACE__
#define __CAN_INTERFACE__
#include "../datatypes.h"



/* can_setup should be called by the user to setup the library and CAN Controller */
void can_setup(io_pin cs_pin, io_pin int_pin);

/* can_receive should be called when retrieving the most recent messages */
/* NO_MESSAGE is returned if no messages are available */
can_message* can_receive(void);

/* can_transmit should be called after populating a message and it's ready to send */
void can_transmit(void);


/* This variable should be used in the user's program to populate a message before */
/* calling can_transmit(). MUST call can_transmit() in-order for this variable */
/* to point to a brand new and empty CAN message */
extern can_message* can_new_msg;







/* This function is for initializing the CAN drivers, and should not be called */
/* by the user unless in a unit test */
void can_initialization(void(*can_setup_func)(io_pin, io_pin), void(*can_poll_func)(void), void(*can_transmit_func)(can_message*), can_message*(*can_receive_func)(void));


#endif

