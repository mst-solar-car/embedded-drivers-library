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
 * This function initializes all the drivers in this library
 *
 * It will run before the main() function does, so it should NEVER be called
 * by the user
 */
#ifndef UNIT_TEST
void __attribute__((constructor)) library_initialization(void)
{
  /* Setup each driver */
  pin_control_initialization(__microcontroller_set_pin_mode, __microcontroller_set_pin_level, __microcontroller_read_pin);
  can_initialization(can_controller_setup, can_controller_poll, can_controller_transmit);

  spi_initialization(NULL, NULL);
}
#endif






/**
 * Include driver implementations
 */
#define __STR(x) #x
#define CUSTOM_DRIVER(driveGroup, name)  __STR(driveGroup/name/name.driver)


/* Custom driver implementation of the Microcontroller */
#ifdef MICROCONTROLLER
  #include CUSTOM_DRIVER(microcontroller, MICROCONTROLLER)
#else
  #error "Unkown microcontroller!"
#endif

/* Custom Driver implementation of the CAN Controller */
#ifdef CAN_CONTROLLER
  #include CUSTOM_DRIVER(can_controller, CAN_CONTROLLER)
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

/* No custom implementation of interrupts */
#include "exception/exception.driver"

/* No custom implementation of utilities */
#include "utils/utils.driver"

