/**
 * This is a file full of directives that can be used as utilities (or helpers)
 *
 * Author: Michael Rouse
 */
#ifndef __UTILITIES_H__
#define __UTILITIES_H__

/**
 * Checking Bits
 */
#define setBitHigh(data, bit) (data |= bit)
#define setBitLow(data, bit)  (data &= ~bit)
#define toggleBit(data, bit)  (data ^= bit)
#define getBit(data, bit)     (data & bit)

#define isBitHigh(data, bit)  (getBit(data, bit) != NULL)
#define isBitLow(data, bit)   (getBit(data, bit) == NULL)

#define leftShift(bits, n)    ((uint8_t)(bits << n))
#define rightShift(bits, n)   ((uint8_t)(bits >> n))



// Shorthand for setting an interrupt
#define INTERRUPT(vector)     void __attribute__((interrupt(vector)))  vector ## _ISR(void) // Assists in creation of interrupts


#endif