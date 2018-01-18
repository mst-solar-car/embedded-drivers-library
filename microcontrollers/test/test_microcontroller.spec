/**
 * This file is the specifications for the TI MSP430F5529,
 * it contains directives that are used to control things in other parts of this
 * library
 */
#ifndef MICROCONTROLLER_SPECS
#define MICROCONTROLLER_SPECS

// Begin spec listings
#define MC_NUM_PINS                   8
#define MC_NUM_PORTS                  1
#define MC_NUM_INTERRUPTABLE_PORTS    0

#define MC_NUM_SPI_BUSES              2

#define MC_CLOCK_HZ                   5 // Clock speed in Hz


//#define MC_NO_SPI         // Uncomment if microcontroller doesn't support SPI
#define MC_NO_INTERRUPTS  // Uncomment if microcontroller doesn't support interrupts
#define MC_NO_WATCHDOG    // Uncomment if microcontroller doesn't have a watchdog timer


#endif