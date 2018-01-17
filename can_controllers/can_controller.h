/**
 * CAN Controller Generic Header File.
 *
 * This file contains things that a driver SHOULD implement.
 *
 * Author: Michael Rouse
 */
#include "../user_config.h"
#include "../datatypes.h"
#include "../utils.h"
#include "../spi/spi.h"
#include "../can/constants.h"
#include "../can/can.h"

#ifndef __CAN_CONTROLLER_H__
#define __CAN_CONTROLLER_H__


/**
 * Functions that the drivers should implement
 */

/**
 * CAN Controller Setup
 *
 * This function should do all the configuration needed for the CAN Controller
 * to function properly.
 */
extern void can_controller_setup(io_pin int_pin, io_pin cs_pin);


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
 * This is used to check for missed interrupts, or to poll when you
 * have no interrupts
 */
extern void can_controller_poll();



#endif