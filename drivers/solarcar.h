/**
 * Solar Car MSP430F5529 Library
 * This library is designed to make writing code simpler for the MSP430F5529.
 *
 * Authors: Michael Rouse
 */
#ifndef __SOLARCAR_H__
#define __SOLARCAR_H__

#include "datatypes.h"











/**
 * Watchdog
 * TODO: watchdog_pet() directive to keep the watchdog timer going
 */
#define watchdog_disable()  WDTCTL = WDTPW + WDTHOLD



/**
 * Interrupts
 */
#define enable_interrupts()  __enable_interrupt();




/**
 * System Clock Initialization
 * Below is FLL magic, just take this for what it is and don't question it
 */
#define CRYSTAL_FREQ_KHZ  32768     // Frequency of the crystal used in kHz
#define MCLK_FREQ_HZ      20000000  // Default frequency in Hz

#define clock_init()    UCSCTL3 &= ~(0x0070);   /* Select XT1CLK (our onboard 32.768kHz crystal) as the FLL reference */ \
                        UCSCTL4 &= ~(0x0070);   /* Select XT1CLK as ACLK */ \
                        uint16_t ratio, dco_div_bits; \
                        uint8_t mode = 0; /* DC0CLK or DC0CLKDIV? */ \
                        uint16_t sysfreq = MCLK_FREQ_HZ / 1000; /* System frequency in kHz */ \
                        ratio = MCLK_FREQ_HZ / CRYSTAL_FREQ_KHZ; /* Ratio of system_freq -> FLL reference freq */ \
                        if (sysfreq > 16000) { ratio >>= 1; mode = 1; } /* Is sysfreq > 16Mhz? If so use DC0CLK rather than DC0CLKDIV */ \
                        else { sysfreq <<= 1; } \
                        while(ratio > 512) { dco_div_bits += FLLD0; ratio >>= 1; } \
                        __bis_SR_register(SCG0); /* Disable the FLL while we change the clocks */ \
                        UCSCTL0 = 0x0000; /* Set the DC0 to the lowest tap setting */ \
                        UCSCTL2 &= ~(0x3FF); /* Clear the 8 LSBs in the register to clear the FLLN bits */ \
                        UCSCTL2 = dco_div_bits | (ratio - 1); /* Datasheet voodoo */ \
                        if (sysfreq <= 630) UCSCTL1 = DCORSEL_0; \
                        else if (sysfreq < 1250) UCSCTL1 = DCORSEL_1; \
                        else if (sysfreq < 2500) UCSCTL1 = DCORSEL_2; \
                        else if (sysfreq < 5000) UCSCTL1 = DCORSEL_3; \
                        else if (sysfreq < 10000) UCSCTL1 = DCORSEL_4; \
                        else if (sysfreq < 20000) UCSCTL1 = DCORSEL_5; \
                        else if (sysfreq < 40000) UCSCTL1 = DCORSEL_6; \
                        else UCSCTL1 = DCORSEL_7; \
                        __bic_SR_register(SCG0); /* Re-enable the FLL */ \
                        if (mode == 1) { UCSCTL4 &= ~(0x0077); UCSCTL4 |= 0x0033; } \
                        else { UCSCTL4 &= ~(0x0077); UCSCTL4 |= 0x0044; } \
                        __delay_cycles(625000)

#endif

/**
 * Include the rest of the drivers
 * This will reduce the number of imports the user needs to add themselves
 */
#include "microcontroller.h"





