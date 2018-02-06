/**
 * Interface for the Pin Control Driver
 *
 * Authors: Michael Rouse
 */
#ifndef __PIN_CONTROL_INTERFACE__
#define __PIN_CONTROL_INTERFACE__
#include "../datatypes.h"

/* Sets a pin to a certain mode (e.g., Input or Output) */
void pin_set_mode(io_pin pin, pin_mode mode);

/* Sets a pin to a level (e.g., High or Low) */
void pin_set_level(io_pin pin, pin_level level);

/* Toggles a pin, sets it High if it is Low, and Low if it is High */
void pin_toggle(io_pin pin);

/* Returns the level of a pin (e.g., High or Low) */
uint8_t pin_read(io_pin pin);

#endif