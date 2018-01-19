/**
 * This file is responsible for importing the appropriate .specs file for
 * the microcontroller, it operates in the exact same way as microcontrollers/importer.h
 *
 * Author: Michael Rouse
 */
#ifndef __MICROCONTROLLER_SPEC_IMPORTER_H__
#define __MICROCONTROLLER_SPEC_IMPORTER_H__

/**
 * ADD MICROCONTROLLERS HERE (as #elif statements)
 */
#ifdef __MSP430F5529__
  // Texas Instruments MSP430F5529
  #include "msp430f5529/ti_msp430f5529.spec"

#endif





// Enforce specification
#ifdef MICROCONTROLLER_SPECS
  // Clock Speed
  #ifndef MC_CLOCK_HZ
    #error "Spec file for microcontroller drivers do not define the 'MC_CLOCK_HZ' directive that is the clock speed in Hertz"
  #endif

  // Warn about no SPI
  #ifdef MC_NO_SPI
    #warning "Microcontroller drivers do not support SPI transmission"
  #else
    #ifndef MC_NUM_SPI_BUSES
      #error "Microcontroller spec does not define the 'MC_NUM_SPI_BUSES' directive for determining the number of SPI buses"
    #endif
  #endif

  // Warn about no Watchdog
  #ifdef MC_NO_WATCHDOG
    #warning "Microcontroller drivers do not support a watchdog timer"
  #endif

  // Warn about no interrupts
  #ifdef MC_NO_INTERRUPTS
    #warning "Microcontroller drivers do not support Interrupts"
  #else
    #ifndef MC_NUM_INTERRUPTABLE_PORTS
      #error "Microcontroller spec does not define the 'MC_NUM_INTERRUPTABLE_PORTS' directive. If microcontroller doesn't support interrupts you need to define the 'MC_NO_INTERRUPTS' directve"
    #endif
  #endif

  // Number of pins
  #ifndef MC_NUM_PINS
    #error "Microcontroller spec does not define the 'MC_NUM_PINS' directive to identify how many pins it has"
  #endif

  // Number of ports
  #ifndef MC_NUM_PORTS
    #warning "Microcontroller spec does not define the 'MC_NUM_PORTS' directive to identify how many ports it has"
  #endif

#else
  // NO Microcontroller specs specified
  #error "Unknown microcontroller specs, please add a *.spec file to your microcontroller driver folder, and add it to the microcontrollers/spec_importer.h file"
#endif


#endif
