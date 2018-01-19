/**
 * Solar Car MSP430F5529 Library
 * This library is designed to make writing code simpler for the MSP430F5529.
 *
 * Authors: Michael Rouse
 */
#include "library.details.h"
#ifndef __SOLARCAR_H__
#define __SOLARCAR_H__
#ifdef __GNUC__


// :)


/**
 * Include the rest of the drivers
 * This will reduce the number of imports the user needs to add themselves
 */
#include "datatypes.h"
#include "config.h"
#include "utils.h"

#include "microcontrollers/importer.h"
#include "can/can.h"
#include "spi/spi.h"






#else
  // Allert the user that they should be using GCC
  #error "You should be using GCC as your compiler!"
#endif
#endif