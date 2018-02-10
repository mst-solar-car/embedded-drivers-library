/**
 * This header file is responsible for defining what specific microcontroller
 * driver the target should be using
 *
 * Authors: Michael Rouse
 */
#ifndef __MICROCONTROLLER_REGISTRATION__
#define __MICROCONTROLLER_REGISTRATION__


#ifdef __MSP430F5529__
  #define MICROCONTROLLER msp430f5529
#endif


#include "msp430f5529/msp430f5529.spec"
#endif