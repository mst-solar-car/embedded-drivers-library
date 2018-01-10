/**
 * This file is a generic importer for a microcontroller
 * It should use directives to determine which microcontroller
 * drivers to import.
 * 
 * To implement a new microcontroller simply add a folder named the model of the microcontroller, 
 * implement a header and source file inside that folder. When ready add a C-precompiler directive 
 * to the list of microcontrollers here (labeled-almost at end of the file). 
 * This is so the compiler can detect the target microcontroller and import the appropriate file.
 * 
 * Your microcontroller driver MUST do the following: 
 *    - Define the __MICROCONTROLLER__ directive 
 *    - Implement the void microcontroller_setup() function that should: 
 *        + Set default pin states
 *        + Set system clock
 *        + Disable watchdog 
 *        + Any other initial configuration that requires NO USER CONFIGURATION
 * 
 *    - Implement the following arrays (see msp430f5529 drivers for example): 
 *        + dir_registers
 *        + out_registers 
 *        + in_registers 
 *        + sel_registers
 *        + port_map 
 *        + bit_map 
 *  
 * I'm not going to type out all the possibilities your driver can do in here, so see MICROCONTROLLERS.md 
 * for a lot more information. 
 * 
 * Author: Michael Rouse
 */
#ifndef __MICROCONTROLLER_IMPORTER_H__
#define __MICROCONTROLLER_IMPORTER_H__

#include "datatypes.h"


/**
 * Functions that the drivers should define 
 */
extern void microcontroller_setup(); 

/**
 * Arrays for pin control (need to be defined in microcontroller driver implementation)
 */
extern const vuint16_t* dir_registers[];  // PxDIR
extern const vuint16_t* out_registers[];  // PxOUT
extern const vuint16_t* in_registers[];   // PxIN
extern const vuint16_t* sel_registers[];  // PxSEL 

extern const uint8_t port_map[];  // Pin4 => P6.7 => PORT6
extern const uint8_t bit_map[];   // Pin4 => P6.7 => BIT7







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
 * ADD MICROCONTROLLERS HERE (as #elif statements)
 */
#if defined(__MSP430F5529__) 
  // Texas Instruments MSP430F5529
  #include "msp430f5529/ti_msp430f5529.h"

#else 
#error "Unknown microcontroller in drivers/microcontroller.h"
#endif






/**
 * Directive Enforcement (and apply default no-ops)
 */
#ifdef __MICROCONTROLLER__ 
  // Interrupts
  #ifndef NO_INTERRUPTS
    #ifndef interrupts_enable()
      #warning "Microcontroller drivers do not define the 'interrupts_enable()' directive, no way to enable interrupts"
      #define interrupts_enable()
    #endif 

    #ifndef interrupts_disable()
      #warning "Microcontroller drivers do not define the 'interrupts_disable()' directive, no way to disable interrupts"
      #define interrupts_disable()
    #endif
  #endif 

  // Watchdog
  #ifndef NO_WATCHDOG 
    #ifndef watchdog_enable() 
      #warning "Microcontroller drivers do not define the 'watchdog_enable()' directive, no way to enable the watchdog timer"
      #define watchdog_enable()
    #endif 
    
    #ifndef watchdog_disable() 
      #warning "Microcontroller drivers do not define the 'watchdog_disable()' directive, no way to disable the watchdog timer"
      #define watchdog_disable() 
    #endif 

    #ifndef watchdog_pet() 
      #warning "Microcontroller drivers do not define the 'watchdog_pet()' directive, how are you going to pet your fluffy doggo?"
      #define watchdog_pet()  
    #endif 
  #endif

  // Clock Frequency
  #ifndef MICROCONTROLLER_CLOCK
    #error "Microcontroller drivers do not define the 'MICROCONTROLLER_CLOCK' directive, please use it to specify clock frequency in Hz"
  #endif 
  

#endif




#endif