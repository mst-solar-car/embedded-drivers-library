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
#if defined(__MSP430F5529__)
  // Texas Instruments MSP430F5529
  #include "msp430f5529/ti_msp430f5529.spec"

#endif







#endif
