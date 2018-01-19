/**
 * This file is responsible for importing the appropriate header file for whatever microcontroller is being used.
 *
 * To implement a new microcontroller simply add a folder named the model of the microcontroller,
 * implement a header and source file inside that folder. When ready add a C-precompiler directive
 * to the list of microcontrollers here (labeled-almost at end of the file).
 * This is so the compiler can detect the target microcontroller and import the appropriate file.
 *
 * Author: Michael Rouse
 */
#ifndef __MICROCONTROLLER_IMPORTER_H__
#define __MICROCONTROLLER_IMPORTER_H__
#include "spec_importer.h"

/**
 * ADD MICROCONTROLLERS HERE (as #elif statements)
 */
#ifdef __MSP430F5529__
  // Texas Instruments MSP430F5529
  #include "msp430f5529/ti_msp430f5529.h"

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
  #ifndef MC_NO_INTERRUPTS
    #ifndef interrupts_enable
      #warning "Microcontroller drivers do not define the 'interrupts_enable()' directive, no way to enable interrupts; define 'NO_INTERRUPTS' if they are not supported"
      #define interrupts_enable()   no_operation()
    #endif

    #ifndef interrupts_disable
      #warning "Microcontroller drivers do not define the 'interrupts_disable()' directive, no way to disable interrupts; define 'NO_INTERRUPTS' if they are not supported"
      #define interrupts_disable()  no_operation()
    #endif

  #else
    // Interrupts not supported, assign no-ops
    #undef interrupts_enable
    #define interrupts_enable()     no_operation()
    #undef interrupts_disable
    #define interrupts_disable()    no_operation()
  #endif

  // Watchdog
  #ifndef MC_NO_WATCHDOG
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
    #undef watchdog_enable
    #define watchdog_enable()       no_operation()
    #undef watchdog_disable
    #define watchdog_disable()      no_operation()
    #undef watchdog_pet
    #define watchdog_pet()          no_operation()
  #endif




#else
  // No microcontroller specified
  #error "Unknown microcontroller in drivers/microcontrollers/microcontroller.h; confirm drivers define the 'MICROCONTROLLER' directive"
#endif






#endif