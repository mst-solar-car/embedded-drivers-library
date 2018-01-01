/**
 * CAN Driver Header File
 *
 * Authors: Michael Rouse
 *
 * This file is the header for the CAN drivers. It defines types, constants,
 * functions, and anything else that is needed to interact with the CAN Bus.
 *
 * This driver splits up the CAN API (functions you use) and the code needed
 * to interact with a CAN Controller. This makes this CAN driver API now completely
 * portable.
 * This interface can be used with (probably) any CAN Controller, all you need to
 * do is write a new CAN Controller implementation (see solarcar_mcp2515.h for details).
 *
 * The CAN driver has the following exposed functions that you can use to send/receive
 * CAN Messages (see declarations below for more):
 *
 *    void can_setup();
 *    can_message* can_receive();
 *    int8_t can_transmit(can_message* msg);
 *    bool can_message_check();
 *
 * Any other functions declared in this header file are considered "private."
 * That means that they should only ever be called from inside the solarcar_can.c
 * file.
 *
 * At the bottom of this file is where you import the header file for the CAN Controller,
 * this way it has access to all of the constants (directives) declared here.
 */
#ifndef __SOLARCAR_CAN_H__
#define __SOLARCAR_CAN_H__

// DO NOT include a CAN Controller implementation header here, do that at the end of this file


//----------------------- User Configuration -----------------------//

#define CAN_ENABLE_INTERRUPTS

//#define CAN_CS_PIN          x   // Pin for the CAN Chip Select
//#define CAN_INTERRUPT_PIN   x   // Pin for the CAN Interrupt line

// Uncommenting the next line will result in corrupt packets being received as CAN Messages (probably do not want this)
//#define CAN_RECEIVE_ERROR_PACKETS


// Change these filters to be the Message IDs that this board should receive
#define CAN_FILTER1         0x000
#define CAN_FILTER2         0x000
#define CAN_FILTER3         0x000
#define CAN_FILTER4         0x000
#define CAN_FILTER5         0x000
#define CAN_FILTER6         0x000

// Adjust these masks so IDs can be checked against the filters (0x000 will make a match with any filter)
#define CAN_MASK1           0x000
#define CAN_MASK2           0x000



//------------------ End of User Configuration ------------------//






// Force the import of solarcar.h
#ifndef __SOLARCAR_H__
#warning "solarcar_can.h included without including solarcar.h, automatically including it"
#include "solarcar.h"
#endif


/**
 * CAN Constants
 */
#define CAN_BUFFER_LENGTH   32
#define CAN_MESSAGE_SIZE    13

#define CAN_TX_SUCCESS      1
#define CAN_TX_BUSY         -1


// CAN Message Statuses
#define CAN_ERROR           0xFFFF
#define CAN_MERROR          0xFFFE
#define CAN_WAKE            0xFFFD
#define CAN_RTR             0xFFFC
#define CAN_OK              0x0001

#define NO_CAN_MESSAGE      NULL


/**
 * CAN Data Types
 */
// can_message is declared in solarcar.h

// Transmit Queue
extern can_message _tx_queue[CAN_BUFFER_LENGTH];
extern can_message* _tx_push_ptr;
extern can_message* _tx_pop_ptr;

// Receive Queue
extern can_message _rx_queue[CAN_BUFFER_LENGTH];
extern can_message* _rx_push_ptr;
extern can_message* _rx_pop_ptr;



/**
 * "Public" Functions
 * These functions should be called by the user
 */

/**
 * Initializes the CAN Driver
 */
void can_setup();

/**
 * Receives a CAN Message
 *
 * @return can_message*   The message received
 */
can_message* can_receive(void);

/**
 * Send a CAN Message
 *
 * @param can_message* msg  The message to send, if NULL it will send whatever is the TX queue
 */
int8_t can_transmit(can_message* msg);

/**
 * Checks if the interrupt that occured was for CAN, and if it was it will receive the message
 * If you are using interrupts, then call this function when the port interrupt occurs.
 *
 * This can also be used to check if an interrupt was missed (by calling it in the main loop)
 *
 * @return bool   TRUE if the interrupt was CAN and was handled, FALSE otherwise
 */
bool can_message_check(void);







/**
 * "Private" Functions
 * These functions should only be called from inside solarcar_can.c
 */

/**
 * This function is further implementation of the can_message_check() function
 */
void _can_handle_interrupt(void);





/**
 * Enforce required-user defined directives
 */
#ifndef CAN_CS_PIN
#error "You MUST define the CAN_CS_PIN directive at the top of solarcar_can.h"
#endif

#ifndef CAN_ENABLE_INTERRUPTS
#warning "The CAN driver will not use interrupts!"
#else
// Make sure the CAN_INTERRUPT_PIN directive is defined if using interrupts
#ifndef CAN_INTERRUPT_PIN
#error "The CAN driver is configured to use interrupts, so you must define the CAN_INTERRUPT_PIN directive at the top of solarcar_can.h"
#endif
#endif




// Include the header file for the CAN Controller here.
#include "solarcar_mcp2515.h"




// Force a CAN Controller implementation
#ifndef __SOLARCAR_CAN_CONTROLLER_H__
#error "You MUST include a CAN Controller implementation at the bottom of solarcar_can.h"
#endif

#endif