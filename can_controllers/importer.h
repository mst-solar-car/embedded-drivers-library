/**
 * This file is responsible for importing the driver for
 * the appropriate CAN Controller.
 *
 * Unfortunately, we can't have the compiler detect what
 * CAN Controller is on the board, so, you'll have to manually
 * change this file in the future.
 *
 * I created this file (even though you'll have to change it)
 * so you don't have to change references to it everywhere.
 *
 * Author: Michael Rouse
 */
#ifndef __CAN_CONTROLLER_IMPORTER_H__
#define __CAN_CONTROLLER_IMPORTER_H__

#ifdef UNIT_TEST
  // Ignore this UNIT_TEST stuff
  #include "can_controller.h"
  #define CAN_CONTROLLER
#else

/**
 * Add CAN Controllers here (and comment out ones that are not in use)
 */
#include "mcp2515/mcp2515.h"


#ifdef CAN_CONTROLLER

#else
  #error "Unkown CAN Controller in can_controllers/importer.h"
#endif

#endif
#endif

