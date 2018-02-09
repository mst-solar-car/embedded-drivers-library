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

/* Include Utilitiy Interfaces */
#include "utils/memory/interface.h"
#include "utils/queue/interface.h"

/* Include driver interfaces that are apart of this library */
#include "can/interface.h"
#include "microcontroller/interface.h"
#include "microcontroller/registration.h"
#include "can_controller/interface.h"
#include "can_controller/registration.h"
#include "spi/interface.h"
#include "pin_control/interface.h"
#include "interrupts/interface.h"







#else
  /* Not using GCC or MSP430 GCC, which they should be */
  #error "You should be using GCC as your compiler!"

#endif


#endif