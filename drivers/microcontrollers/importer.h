/**
 * This file is responsible for importing the appropriate header file for whatever microcontroller is being used.
 *
 * To implement a new microcontroller simply add a folder named the model of the microcontroller,
 * implement a header and source file inside that folder. When ready add a C-precompiler directive
 * to the list of microcontrollers here (labeled-almost at end of the file).
 * This is so the compiler can detect the target microcontroller and import the appropriate file.
 *
 * Your microcontroller driver MUST do the following:
 *    - Define the MICROCONTROLLER directive
 *    - Implement the void microcontroller_setup() function that should:
 *        + Set default pin states
 *        + Set system clock
 *        + Disable watchdog
 *        + Any other initial configuration that requires NO USER CONFIGURATION
 *
 *    - Implement the following arrays (see msp430f5529 drivers for example):
 *        + dir_registers
 *        + out_registers
 *        + in_registers
 *        + sel_registers
 *        + port_map
 *        + bit_map
 *
 * I'm not going to type out all the possibilities your driver can do in here, so see MICROCONTROLLERS.md
 * for a lot more information.
 *
 * Author: Michael Rouse
 */
#ifndef __MICROCONTROLLER_IMPORTER_H__
#define __MICROCONTROLLER_IMPORTER_H__

/**
 * ADD MICROCONTROLLERS HERE (as #elif statements)
 */
#if defined(__MSP430F5529__)
  // Texas Instruments MSP430F5529
  #include "msp430f5529/ti_msp430f5529.h"

#elif defined(UNIT_TEST)
  // Unit Test Microcontroller
  #include "test/test_microcontroller.h.test"


#endif







/**
 * Directive Enforcement (and apply default no-ops)
 */
#ifdef MICROCONTROLLER
  #ifndef no_operation
    #warning "Microcontroller drivers do not define the 'no_operation()' directive, lines performing no-op operations will be removed by optimizer"
    #define no_operation()   // Nothing, these lines will be removed by compiler
  #endif


  // Interrupts
  #ifndef NO_INTERRUPTS
    #ifndef interrupts_enable
      #warning "Microcontroller drivers do not define the 'interrupts_enable()' directive, no way to enable interrupts; define 'NO_INTERRUPTS' if they are not supported"
      #define interrupts_enable()   no_operation()
    #endif

    #ifndef interrupts_disable
      #warning "Microcontroller drivers do not define the 'interrupts_disable()' directive, no way to disable interrupts; define 'NO_INTERRUPTS' if they are not supported"
      #define interrupts_disable()  no_operation()
    #endif

    #ifndef MICROCONTROLLER_NUM_INTERRUPTABLE_PORTS
      #warning "Microcontroller drivers do not define the 'MICROCONTROLLER_NUM_INTERRUPTABLE_PORTS' directive, no way to know how many ports support interrupts, resulting in wasted memory"
      #define MICROCONTROLLER_NUM_INTERRUPTABLE_PORTS 8
    #endif

  #else
    // Interrupts not supported, assign no-ops
    #define interrupts_enable()     no_operation()
    #define interrupts_disable()    no_operation()

    #define MICROCONTROLLER_NUM_INTERRUPTABLE_PORTS   0
  #endif


  // Watchdog
  #ifndef NO_WATCHDOG
    #ifndef watchdog_enable
      #warning "Microcontroller drivers do not define the 'watchdog_enable()' directive, no way to enable the watchdog timer; define 'NO_WATCHDOG' if not supported"
      #define watchdog_enable()     no_operation()
    #endif

    #ifndef watchdog_disable
      #warning "Microcontroller drivers do not define the 'watchdog_disable()' directive, no way to disable the watchdog timer; define 'NO_WATCHDOG' if not supported"
      #define watchdog_disable()    no_operation()
    #endif

    #ifndef watchdog_pet
      #warning "Microcontroller drivers do not define the 'watchdog_pet()' directive, how are you going to pet your fluffy doggo? Define 'NO_WATCHDOG' if not supported"
      #define watchdog_pet()        no_operation()
    #endif

  #else
    // Watchdog not supported, assign no-ops
    #define watchdog_enable()       no_operation()
    #define watchdog_disable()      no_operation()
    #define watchdog_pet()          no_operation()
  #endif

  // Clock Frequency
  #ifndef MICROCONTROLLER_CLOCK_HZ
    #error "Microcontroller drivers do not define the 'MICROCONTROLLER_CLOCK_HZ' directive, please use it to specify clock frequency in Hz"
  #endif

  // SPI
  #ifndef NO_SPI
    #ifndef spi_busy_check
      #error "Microcontroller drivers do not define the 'spi_busy_check()' directive, please define it."
    #endif

    #ifndef spi_busy_check2
      #error "Microcontroller drivers do not define the 'spi_busy_check2()' directive, please do so."
    #endif

    #ifndef spi_send_data
      #error "Microcontroller drivers do not define the 'spi_send_data(data)' directive, please implemented it."
    #endif

    #ifndef spi_get_data
      #error "Microcontroller drivers do not define the 'spi_get_data()' directive, please define it."
    #endif

  #else
    #warning "Microcontroller drivers do not support SPI :("
  #endif


#else
  // No microcontroller specified
  #error "Unknown microcontroller in drivers/microcontrollers/microcontroller.h; confirm drivers define the 'MICROCONTROLLER' directive"
#endif



#endif