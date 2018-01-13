/**
 * CAN Driver Header
 *
 * Author: Michael Rouse
 */
#ifndef __CAN_H__
#define __CAN_H__

#include "../datatypes.h"

#include "../microcontrollers/importer.h"


/**
 * CAN Constants
 */
#define CAN_BUFFER_LENGTH   32
#define CAN_MESSAGE_SIZE    13

// CAN Message Statuses
#define CAN_ERROR           0xFFFF
#define CAN_MERROR          0xFFFE
#define CAN_WAKE            0xFFFD
#define CAN_RTR             0xFFFC
#define CAN_OK              0x0001


/**
 * "Public" Functions
 * These should be called by the user
 */
void can_setup(io_pin cs_pin, io_pin int_pin);
can_message* can_receive(void);
bool can_transmit(can_message* msg);
bool can_message_check(void);



/**
 * "Private" Functions
 * These functions should only be called from inside can.c
 */
void _can_handle_interrupt(void);



/**
 * "Private" Variables
 * Not to be accessed by the user
 */
extern can_message _tx_queue[CAN_BUFFER_LENGTH];
extern can_message* _tx_push;
extern can_message* _tx_pop;

extern can_message _rx_queue[CAN_BUFFER_LENGTH];
extern can_message* _rx_push;
extern can_message* _rx_pop;

extern io_pin _can_int_pin;



#include "../can_controllers/importer.h"

#endif
