/**
 * Bit Manipulation API
 *
 * Authors: Michael Rouse
 */
#ifndef __BIT_MANIPULATION_INTERFACE__
#define __BIT_MANIPULATION_INTERFACE__

/* Sets bits high */
#define bits_set_high(value, bits)  ((value) |= (bits))

/* Sets bits low */
#define bits_set_low(value, bits)   ((value) &= ~(bits))

/* Toggles a bit */
#define bits_toggle(value, bits)    ((value) ^= (bits))

/* Gets a bit */
#define bits_get(value, bits)       ((value) & (bits))

/* Checks if a bit is High or Low */
#define bits_is_high(value, bits)   (bits_get(value, bits) != 0x00)
#define bits_is_low(value, bits)    (bits_get(value, bits) == 0x00)

/* Bit shifting */
#define bits_left_shift(value, n)   ((value) << (n))
#define bits_right_shift(value, n)  ((value) >> (n))

#endif