/**
 * This file is responsible for loading the approrpiate CAN Controller drivers
 *
 * Authors: Michael Rouse
 */
#include "registration.h"

#ifndef __STR
#define __STR(x) #x
#endif


#ifndef CAN_CONTROLLER
  #error "Unkown CAN Controller! Please specify definition for 'CAN_CONTROLLER' in can_controller/registration.h"
#else

#define LOAD_CANCONTROLLER_DRIVERS(name, ext) __STR(name/name.ext)

/*#include LOAD_CANCONTROLLER_DRIVERS(CAN_CONTROLLER, spec)*/

#ifdef LOAD_CUSTOM_DRIVER_CODE
  #include LOAD_CANCONTROLLER_DRIVERS(CAN_CONTROLLER, driver)
#endif

#endif