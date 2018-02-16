/**
 * This file is responsible for loading the approrpiate microcontroller drivers
 *
 * Authors: Michael Rouse
 */
#include "registration.h"

#ifndef __STR
#define __STR(x) #x
#endif


#ifndef MICROCONTROLLER
  #error "Unkown Microcontroller! Please specify definition for 'MICROCONTROLLER' in microcontroller/registration.h"
#else

#define LOAD_MICROCONTROLLER_PRODUCTION_HEADER(name)  <name.h>
#define LOAD_MICROCONTROLLER_DRIVER_INTERFACE(name)   __STR(name/interface.h)
#define LOAD_MICROCONTROLLER_MOCK(name)               __STR(name/name.mock)
#define LOAD_MICROCONTROLLER_DRIVERS(name, ext)       __STR(name/name.ext)


/* Load the spec and driver file here */
#ifndef UNIT_TEST
#include LOAD_MICROCONTROLLER_PRODUCTION_HEADER(MICROCONTROLLER)
#else
#include LOAD_MICROCONTROLLER_MOCK(MICROCONTROLLER)
#endif

#include LOAD_MICROCONTROLLER_DRIVER_INTERFACE(MICROCONTROLLER)
#include LOAD_MICROCONTROLLER_DRIVERS(MICROCONTROLLER, spec)

#ifdef LOAD_CUSTOM_DRIVER_CODE
  #include LOAD_MICROCONTROLLER_DRIVERS(MICROCONTROLLER, driver)
#endif

#endif
