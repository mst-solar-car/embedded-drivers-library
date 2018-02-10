/**
 * This file implements a global initialization function that is responsible
 * for initializing (not setting up) all of the drivers in the library.
 *
 * Initilization is different from Setup in that setup is performed by a user
 * with user configuration, initialization is only configuring the drivers
 * (dependency injection, etc...)
 *
 *
 * Authors: Michael Rouse
 */
#include "library.h"
#include <stdio.h>









/**
 * Include driver implementations
 */
#define RUN_SPEC_FILE_LIKE_C_FILE

/* Custom driver implementation of the Microcontroller */
#ifdef MICROCONTROLLER
  #include CUSTOM_DRIVER(microcontroller, MICROCONTROLLER, spec)
  #include CUSTOM_DRIVER(microcontroller, MICROCONTROLLER, driver)
#else
  #error "Unkown microcontroller!"
#endif

/* Custom Driver implementation of the CAN Controller */
#ifdef CAN_CONTROLLER
  #include CUSTOM_DRIVER(can_controller, CAN_CONTROLLER, driver)
#else
  #warning "Unkown CAN Controller!"
#endif

/* No custom implementation of SPI */
#include "spi/spi.driver"

/* No custom implementation of CAN */
#include "can/can.driver"

/* No custom implementation of pin_control */
#include "pin_control/pin_control.driver"

/* No custom implentation of interrupts */
#include "interrupts/interrupts.driver"

/* No custom implementation of utilities */
#include "utils/utils.driver"


#undef RUN_SPEC_FILE_LIKE_C_FILE








/**
 * This function initializes all the drivers in this library
 *
 * It will run before the main() function does, so it should NEVER be called
 * by the user.
 *
 * This function MUST be at the end of this file, if it's not you'll dereference NULL pointers out the ass :)
 * when the microcontroller initialization tries to access any of the register arrays
 */
#ifndef UNIT_TEST
void __attribute__((constructor)) library_initialization(void)
{
  /* Setup each driver */
  microcontroller_initialization();

  pin_control_initialization(__microcontroller_set_pin_mode, __microcontroller_set_pin_level, __microcontroller_read_pin);
  can_initialization(can_controller_setup, can_controller_poll, can_controller_transmit);

  spi_initialization(NULL, NULL);
}
#endif