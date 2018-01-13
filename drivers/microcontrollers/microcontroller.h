/**
 * This file is a header file that contains stuff needed by microcontroller implementations.
 *
 * Your microcontroller implementation should include this header file
 *
 * Author: Michael Rouse
 */
#include "../user_config.h"
#include "../datatypes.h"

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
#define getIEReg(var, port, ...)    var = ieReg(port); if (var == NO_REGISTER) return __VA_ARGS__
#define getIFGReg(var, port, ...)   var = ifgReg(port); if (var == NO_REGISTER) return __VA_ARGS__


/**
 * Functions for controlling pins (microcontroller.c--NOT driver implementation)
 */
void setPinMode(io_pin pin, pin_mode mode);
void setPinLevel(io_pin pin, pin_level level);
void togglePinLevel(io_pin pin);
pin_level readPin(io_pin pin);



/**
 * Directives to mark ports as INPUT or OUTPUT
 */
#define inputPin(pin)     setPinMode(pin, INPUT)  // Configures a pin for INPUT
#define setInput(pin)     inputPin(pin)           // inputPin alias

#define outputPin(pin)    setPinMode(pin, OUTPUT) // Configures a pin for OUTPUT
#define setOutput(pin)    outputPin(pin)          // outputPin alias

#define interruptPin(pin) setPinMode(pin, Interrupt) // Configures pin for an interrupt
#define setInterrupt(pin) interruptPin(pin)           // interruptPin alias


/**
 * Directives for controlling pins
 */
#define setHigh(pin)      setPinLevel(pin, HIGH) // Sets a pin HIGH
#define setPinHigh(pin)   setHigh(pin)           // Alias

#define setLow(pin)       setPinLevel(pin, LOW)  // Sets a pin LOW
#define setPinLow(pin)    setLow(pin)            // Alias

#define toggle(pin)       togglePinLevel(pin)    // Toggles a pin HIGH or LOW
#define togglePin(pin)    toggle(pin)            // Alias

#define read(pin)         readPin(pin)           // Reads value of bit in register


/**
 * Directive for direct pin manipulation
 * Probably for unit testing and stuff
 */
#define setRegister(reg, bits)           *reg = bits
#define setRegisterBitHigh(reg, bit)     *reg |= bit
#define setRegisterBitLow(reg, bit)      *reg &= ~bit
#define toggleRegisterBit(reg, bit)      *reg ^= bit


/**
 * Checking Bits
 */
#define getBit(data, bit)   (data & bit)

#define isLow(data, bit)    (getBit(data, bit) != bit)
#define isHigh(data, bit)   (getBit(data, bit) == bit)

#define leftShift(bits, n)  ((uint8_t)(bits << n))
#define rightShift(bits, n) ((uint8_t)(bits >> n))


/**
 * Arduino-Like Aliases
 */
#define pinMode(pin, mode)        setPinMode(pin, mode)
#define digitalWrite(pin, state)  setPinLevel(pin, state)
#define digitalRead(pin)          readPin(pin)


/**
 * Misc things
 */
#define INTERRUPT(vector)     void __attribute__((interrupt(vector)))  vector ## _ISR(void) // Assists in creation of interrupts


// Make sure bit definitions are defined (unit testing)
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






#endif