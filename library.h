/**
 * Embedded Drivers Library
 *
 * This library is designed to allow for a common library for drivers across
 * all boards used for the Missouri S&T Solar Car Team
 *
 *
 * Authors: Michael Rouse
 */
#ifndef __LIBRARY__
#define __LIBRARY__
#ifdef __GNUC__


/* Include drivers that are apart of this library */
#include "can/interface.h"
#include "microcontroller/interface.h"
#include "microcontroller/registration.h"
#include "spi/interface.h"
#include "pin_control/interface.h"
#include "interrupts/interface.h"







#else
  /* Not using GCC or MSP430 GCC, which they should be */
  #error "You should be using GCC as your compiler!"

#endif
/* Aliases for making things look nice when importing this file and the .c file */
#define IMPORT_DRIVER_IMPLEMENTATION(driveGroup, implementation)  __STR(driveGroup/implementation/implementation.driver)

#endif