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
  #include "test/test_microcontroller.h"


#endif







/**
 * Directive Enforcement (and apply default no-ops)
 */
#ifdef MICROCONTROLLER
  #ifndef NO_OP
    #warning "Microcontroller drivers do not define the 'NO_OP' directive, lines performing no-op operations will be removed by optimizer"
    #define NO_OP   // Nothing, these lines will be removed by compiler
  #endif 

  // Interrupts
  #ifndef NO_INTERRUPTS
    #ifndef interrupts_enable
      #warning "Microcontroller drivers do not define the 'interrupts_enable()' directive, no way to enable interrupts"
      #define interrupts_enable()   NO_OP 
    #endif 

    #ifndef interrupts_disable
      #warning "Microcontroller drivers do not define the 'interrupts_disable()' directive, no way to disable interrupts"
      #define interrupts_disable()  NO_OP
    #endif
  #endif 

  // Watchdog
  #ifndef NO_WATCHDOG 
    #ifndef watchdog_enable
      #warning "Microcontroller drivers do not define the 'watchdog_enable()' directive, no way to enable the watchdog timer"
      #define watchdog_enable()     NO_OP 
    #endif 
    
    #ifndef watchdog_disable
      #warning "Microcontroller drivers do not define the 'watchdog_disable()' directive, no way to disable the watchdog timer"
      #define watchdog_disable()    NO_OP 
    #endif 

    #ifndef watchdog_pet
      #warning "Microcontroller drivers do not define the 'watchdog_pet()' directive, how are you going to pet your fluffy doggo?"
      #define watchdog_pet()        NO_OP 
    #endif 
  #endif

  // Clock Frequency
  #ifndef MICROCONTROLLER_CLOCK_HZ
    #error "Microcontroller drivers do not define the 'MICROCONTROLLER_CLOCK_HZ' directive, please use it to specify clock frequency in Hz"
  #endif 
  
#else 
#error "Unknown microcontroller in drivers/microcontrollers/microcontroller.h"
#endif



#endif 