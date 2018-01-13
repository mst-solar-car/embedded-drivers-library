/**
 * CAN Controller Generic Header File.
 *
 * This file contains things that a driver SHOULD implement.
 *
 * Author: Michael Rouse
 */
#include "../datatypes.h"
#include "../spi/spi.h"
#include "../can/can.h"

#ifndef __CAN_CONTROLLER_H__
#define __CAN_CONTROLLER_H__


/**
 * Variables you need to deal with
 */
extern io_pin _can_controller_cs_pin;



/**
 * Functions that the drivers should implement
 */

/**
 * CAN Controller Setup
 *
 * This function should do all the configuration needed for the CAN Controller
 * to function properly.
 *
 *
 */
extern void can_controller_setup(io_pin cs_pin);


/*
 * CAN Controller Transmit
 *
 * This function should send a CAN Message to the CAN Controller and then transmit
 * it on the CAN Bus.
 *
 * @param can_message* msg  The CAN Message to transmit
 * @return bool             True if the message was able to be sent, False if not able to be sent (e.g., CAN was busy)
 */
extern bool can_controller_transmit(can_message* msg);


/**
 * CAN Controller Get Message
 *
 * Reads the data of a received CAN Message from the MCP2515 and returns it
 * as a pointer to a can_message.
 *
 * @param can_message* out   The message received
 */
extern void can_controller_get_message(can_message* out);



#endif