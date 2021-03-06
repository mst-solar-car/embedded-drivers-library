/**
 * DO NOT USE THIS FILE. Instead, include "library.h"
 *
 * If the user includes this file they will be greeted with errors on top of errors.
 *
 * This is to help ease the user into the breaking changes caused by v1.0 from
 * previous versions. Once all errors are fixed they will only see a warning
 * about how they should be including "library.h" and not "solarcar.h"
 *
 * Once boards have been transitioned to this file, it should probably be removed.
 *
 * Authors: Michael Rouse
 */
#ifndef __SOLARCAR_H__
#define __SOLARCAR_H__
#define __LIBRARY_COMPATABILITY_MODE__

#warning You are using 'solarcar.h', this file no longer exists. Please switch to using 'library.h' after switching to new function calls and reading documentation.

#include "library.h"

/**
 * Depreciated functions
 */
#define USE_NEW(msg) __attribute__((error("Change to " STR(msg))))

// Pin Control
void USE_NEW("pin_set_mode(pin, mode)")   pinSetMode(io_pin pin, pin_mode mode);
void USE_NEW("pin_set_level(pin, level)") setPinLevel(io_pin pin, pin_level level);
void USE_NEW("pin_read(pin)")             readPin(io_pin pin);
void USE_NEW("pin_set_mode(pin, Input)")  inputPin(io_pin pin);
void USE_NEW("pin_set_mode(pin, Output")  outputPin(io_pin pin);
void USE_NEW("pin_set_level(pin, High)")  setPinHigh(io_pin pin);
void USE_NEW("pin_set_level(pin, Low)")   setPinLow(io_pin pin);
void USE_NEW("pin_toggle(pin)")           togglePin(io_pin pin);
void USE_NEW("pin_read(pin) != Low")      isPinHigh(io_pin pin);
void USE_NEW("pin_read(pin) == Low")      isPinLow(io_pin pin);

// Interrupts
void USE_NEW("interrupt_attach(pin, func)") attachInterrupt(io_pin pin, void(*func)(void));

void USE_NEW("delay_millis(milliseconds)") delayMillis(uint16_t milliseconds);


#endif