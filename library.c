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
#define LOAD_CUSTOM_DRIVER_CODE


/* Custom driver implementation of the Microcontroller */
#include "microcontroller/loader.h"

/* Custom Driver implementation of the CAN Controller */
#include "can_controller/loader.h"

#include "spi/spi.driver"
#include "can/can.driver"
#include "pin_control/pin_control.driver"
#include "interrupts/interrupts.driver"
#include "utils/utils.driver"


#undef LOAD_CUSTOM_DRIVER_CODE
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
void __attribute__((constructor(10000))) library_initialization(void)
{
  /* Setup each driver */
  microcontroller_initialization();

  pin_control_initialization(__microcontroller_set_pin_mode, __microcontroller_set_pin_level, __microcontroller_read_pin);
  can_initialization(can_controller_setup, can_controller_poll, can_controller_transmit);

  spi_initialization(__microcontroller_spi_setup, __microcontroller_spi_transmit);

  can_controller_initialization(spi_transmit, pin_set_mode, pin_set_level, pin_read, interrupt_attach, __can_add_to_receive_queue);
}
#endif