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
#ifndef __GNUC__
#error "You need to be using GCC as your compiler!"
#endif

#ifdef UNIT_TEST
#include <stdlib.h>
#endif

#include "datatypes.h"

/* Include Utility Interfaces */
#include "utils/interface.h"


/* Include driver interfaces that are apart of this library */
#undef LOAD_CUSTOM_DRIVER_CODE
#undef RUN_SPEC_FILE_LIKE_C_FILE

#include "can/interface.h"
#include "microcontroller/interface.h"
#include "microcontroller/loader.h"
#include "can_controller/interface.h"
#include "can_controller/loader.h"
#include "spi/interface.h"
#include "pin_control/interface.h"
#include "interrupts/interface.h"



#endif
