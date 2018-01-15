/**
 * This file is a header file that contains stuff needed by microcontroller implementations.
 *
 * Your microcontroller implementation should include this header file
 *
 * Author: Michael Rouse
 */
#include "../user_config.h"
#include "../datatypes.h"
#include "../utils.h"

#ifndef __MICROCONTROLLER_H__
#define __MICROCONTROLLER_H__


/**
 * Functions that the drivers should define
 */
extern void microcontroller_setup(void) __attribute__((constructor));


/**
 * Arrays for pin control (need to be defined in microcontroller driver implementation)
 */
extern const vuint16_t* dir_registers[];  // PxDIR
extern const vuint16_t* out_registers[];  // PxOUT
extern const vuint16_t* in_registers[];   // PxIN
extern const vuint16_t* sel_registers[];  // PxSEL
extern const vuint16_t* ies_registers[];  // PxIES  (Interrupt Edge Select)
extern const vuint16_t* ie_registers[];   // PxIE   (Intterupt Enable)
extern const vuint16_t* ifg_registers[];  // PxIFG  (Interrupt Flag)

extern const uint8_t port_map[];          // Pin4 => P6.7 => PORT6
extern const uint8_t bit_map[];           // Pin4 => P6.7 => BIT7




// Everything below this line is not important to microcontroller driver implementation
// Everything below this line should only be used in microcontroller.c


// Array helper functions
#define pinPort(pin)  (port_map[pin])
#define pinBit(pin)   (bit_map[pin])
#define dirReg(port)  ((vuint8_t*) dir_registers[port])
#define outReg(port)  ((vuint8_t*) out_registers[port])
#define inReg(port)   ((vuint8_t*) in_registers[port])
#define selReg(port)  ((vuint8_t*) sel_registers[port])
#define iesReg(port)  ((vuint8_t*) ies_registers[port])
#define ieReg(port)   ((vuint8_t*) ie_registers[port])
#define ifgReg(port)  ((vuint8_t*) ifg_registers[port])

#define getPinPort(var, pin, ...)   var = pinPort(pin); if (var == NO_PORT) return __VA_ARGS__
#define getPinBit(var, pin, ...)    var = pinBit(pin);  if (var == NO_BIT)  return __VA_ARGS__
#define getDirReg(var, port, ...)   var = dirReg(port); if (var == NO_REGISTER) return __VA_ARGS__
#define getOutReg(var, port, ...)   var = outReg(port); if (var == NO_REGISTER) return __VA_ARGS__
#define getInReg(var, port, ...)    var = inReg(port);  if (var == NO_REGISTER) return __VA_ARGS__
#define getSelReg(var, port, ...)   var = selReg(port); if (var == NO_REGISTER) return __VA_ARGS__
#define getIESReg(var, port, ...)   var = iesReg(port); if (var == NO_REGISTER) return __VA_ARGS__
#define getIEReg(var, port, ...)    var = ieReg(port);  if (var == NO_REGISTER) return __VA_ARGS__
#define getIFGReg(var, port, ...)   var = ifgReg(port); if (var == NO_REGISTER) return __VA_ARGS__


/**
 * Functions for controlling pins (microcontroller.c--NOT driver implementation)
 */
void setPinMode(io_pin pin, pin_mode mode);
void setPinLevel(io_pin pin, pin_level level);
void togglePinLevel(io_pin pin);
pin_level readPin(io_pin pin);

void attachInterrupt(io_pin pin, void(*func)(void));
#define nonPinInterrupt(vector)   void __attribute__((interrupt(vector)))  vector ## _ISR(void) // Macro for users to define non-pin interrupts (timers, etc...)


/**
 * Aliases for pin control functions
 */
#define inputPin(pin)     setPinMode(pin, Input)      // Configures a pin for INPUT
#define outputPin(pin)    setPinMode(pin, Output)     // Configures a pin for OUTPUT

#define setPinHigh(pin)   setPinLevel(pin, High)    // Sets a pin HIGH
#define setPinLow(pin)    setPinLevel(pin, Low)     // Sets a pin LOW
#define togglePin(pin)    togglePinLevel(pin)       // Sets HIGH if LOW, and LOW if HIGH

#define isPinHigh(pin)    (readPin(pin) == High)    // Tells if a pin is High
#define isPinLow(pin)     (readPin(pin) == Low)     // Tells if a pin is Low

/**
 * Directive for direct pin manipulation
 * Probably for unit testing and stuff
 */
#define setRegister(reg, bits)           *reg = bits
#define setRegisterBitHigh(reg, bit)     setBitHigh(*reg, bit)
#define setRegisterBitLow(reg, bit)      setBitLow(*reg, bit)
#define toggleRegisterBit(reg, bit)      toggleBit(*reg, bit)



/**
 * "Private" Interrupt Stuff
 */
extern void _dispatchInterrupt(uint8_t vector, uint8_t port);

// Used so microcontroller driver can register interrupt vectors
#define REGISTER_PIN_INTERRUPT(vector, port)   void __attribute__((interrupt(vector)))  __ ## vector ## _ISR(void) { \
                                                      _dispatchInterrupt(vector, port);\
                                                    }


// Make sure bit definitions are defined (unit testing)
#define _nbSet(o, b, n) if (b == BIT ## n) o = n
#define _numberBit(o, b) _nbSet(o, b, 0); else _nbSet(o, b, 1); else _nbSet(o, b, 2); else _nbSet(o, b, 3); else _nbSet(o, b, 4); else _nbSet(o, b, 5); else _nbSet(o, b, 6); else _nbSet(o, b, 7); \
                         else _nbSet(o, b, 8); else _nbSet(o, b, 9); else o = -1

#ifndef BIT0
#define BIT0      (0x0001)
#endif

#ifndef BIT1
#define BIT1      (0x0002)
#endif

#ifndef BIT2
#define BIT2      (0x0004)
#endif

#ifndef BIT3
#define BIT3      (0x0008)
#endif

#ifndef BIT4
#define BIT4      (0x0010)
#endif

#ifndef BIT5
#define BIT5      (0x0020)
#endif

#ifndef BIT6
#define BIT6      (0x0040)
#endif

#ifndef BIT7
#define BIT7      (0x0080)
#endif

#ifndef BIT8
#define BIT8      (0x0100)
#endif

#ifndef BIT9
#define BIT9      (0x0200)
#endif

#ifndef BITA
#define BITA      (0x0400)
#endif

#ifndef BITB
#define BITB      (0x0800)
#endif

#ifndef BITC
#define BITC      (0x1000)
#endif

#ifndef BITD
#define BITD      (0x2000)
#endif

#ifndef BITE
#define BITE      (0x4000)
#endif

#ifndef BITF
#define BITF      (0x8000)
#endif


#ifndef BIT10
#define BIT10     BITA
#endif

#ifndef BIT11
#define BIT11     BITB
#endif

#ifndef BIT12
#define BIT12     BITC
#endif

#ifndef BIT13
#define BIT13     BITD
#endif

#ifndef BIT14
#define BIT14     BITE
#endif

#ifndef BIT15
#define BIT15     BITF
#endif






#endif
