/**
 * Header file for the MSP430f5529.
 *
 * This file will contain directives that the user can use, as well as exposed
 * functions specific to the msp430f5529 that the user can use.
 *
 * Authors: Michael Rouse
 */
#ifndef __MSP430F5529_H__
#define __MSP430F5529_H__

#include "../../datatypes.h"


/* Delay for x milliseconds */
#define delay_millis(x)   __delay_cycles(x * (MC_CLOCK_SPEED_HZ / 1000))

#define no_operation()    _no_operation()


/* Watchdog */
#define watchdog_disable()      WDTCTL = WDTPW + WDTHOLD
#define watchdog_enable()       WDTCTL = WDT_ARST_1000
#define watchdog_pet()          WDTCTL = WDTPW + WDTCNTCL




#endif