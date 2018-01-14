/**
 * CAN Driver Header
 *
 * Author: Michael Rouse
 */
#ifndef __CAN_H__
#define __CAN_H__

#include "../user_config.h"
#include "constants.h"
#include "../datatypes.h"
#include "../utils.h"
#include "../microcontrollers/importer.h"
#include "../can_controllers/importer.h"



/**
 * "Public" Functions
 * These should be called by the user
 */
void can_setup(io_pin cs_pin, io_pin int_pin);
can_message* can_receive(void);
bool can_transmit(can_message* msg);
bool can_message_check(void);
can_message* can_new_message(void);



/**
 * "Private" Functions
 * These functions should only be called from inside can.c
 */
void _can_handle_interrupt(void);



#endif
