/**
 * This file is a header file that contains stuff needed by microcontroller implementations.
 * 
 * Your microcontroller implementation should include this header file
 * 
 * Author: Michael Rouse
 */
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

extern const uint8_t port_map[];  // Pin4 => P6.7 => PORT6
extern const uint8_t bit_map[];   // Pin4 => P6.7 => BIT7




// Everything below this line is not important to microcontroller driver implementation
// Everything below this line should only be used in microcontroller.c


// Array helper functions
#define getPinPort(pin)     (port_map[pin])
#define getPinBit(pin)      (bit_map[pin])
#define getDirReg(port)     ((vuint8_t*) dir_registers[port])
#define getOutReg(port)     ((vuint8_t*) out_registers[port])
#define getInReg(port)      ((vuint8_t*) in_registers[port])
#define getSelReg(port)     ((vuint8_t*) sel_registers[port])


/**
 * Functions for controlling pins (microcontroller.c--NOT driver implementation)
 */
void setPinMode(uint8_t pin, uint8_t mode); 
void setPinLevel(uint8_t pin, uint8_t level);
void togglePinLevel(uint8_t pin);
uint8_t readPin(uint8_t pin);



/**
 * Directives to mark ports as INPUT or OUTPUT
 */
#define inputPin(pin)     setPinMode(pin, INPUT)  // Configures a pin for INPUT
#define setInput(pin)     inputPin(pin)           // inputPin alias

#define outputPin(pin)    setPinMode(pin, OUTPUT) // Configures a pin for OUTPUT
#define setOutput(pin)    outputPin(pin)          // outputPin alias


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



// BIT definitions for masks and stuff
#ifndef BIT0 
#define BIT0      0x01
#endif 

#ifndef BIT1 
#define BIT1      0x02
#endif 

#ifndef BIT2 
#define BIT2      0x03
#endif 

#ifndef BIT3 
#define BIT3      0x04
#endif 

#ifndef BIT4 
#define BIT4      0x05
#endif 

#ifndef BIT5
#define BIT5      0x06
#endif 

#ifndef BIT6      
#define BIT6      0x07
#endif 

#ifndef BIT7
#define BIT7      0x08
#endif 

#ifndef BIT8
#define BIT8      0x09
#endif 






#endif