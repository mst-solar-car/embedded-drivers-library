/**
 * Implementation of generic microcontroller stuff 
 * 
 * Author: Michael Rouse
 */
#include "microcontroller.h"


/**
 * Used to mark a pin as INPUT or OUTPUT 
 * 
 * @param uint8_t pin   The pin to change the mode of 
 * @param uint8_t mode  The mode (INPUT or OUTPUT) 
 */
void setPinMode(uint8_t pin, uint8_t mode) 
{
  uint8_t port = getPinPort(pin);
  uint8_t bit = getPinBit(pin); 
  
  if (port == NO_PORT) return; // Can't set the mode of this pin

  vuint8_t *dirReg; 
  vuint8_t *outReg; 

  dirReg = getDirReg(port); 
  outReg = getOutReg(port); 

  // Set the pin mode
  if (mode == INPUT) { 
    // INPUT
    setRegisterBitLow(dirReg, bit);
  }
  else { 
    // OUTPUT
    setRegisterBitHigh(dirReg, bit);
  }
}


/**
 * Used to set a pin HIGH or LOW 
 * 
 * @param uint8_t pin     The pin to change the state of 
 * @param uint8_t level   The new pin state, HIGH or LOW
 */
void setPinLevel(uint8_t pin, uint8_t level)
{
  uint8_t port = getPinPort(pin);
  uint8_t bit = getPinBit(pin); 

  if (port == NO_PORT) return; // Can't change level

  vuint8_t *outReg = getOutReg(port); 
  
  if (level == HIGH) { 
    // HIGH
    setRegisterBitHigh(outReg, bit);
  }
  else { 
    // LOW 
    setRegisterBitLow(outReg, bit);
  }
}


/**
 * Sets a pin HIGH if it's LOW, and LOW if it's HIGH 
 * 
 * @param uint8_t pin   The pin to toggle
 */
void togglePinLevel(uint8_t pin)
{
  uint8_t port = getPinPort(pin); 
  uint8_t bit = getPinBit(pin); 

  if (port == NO_PORT) return; // Can't toggle

  vuint8_t *outReg = getOutReg(port); 
  
  // Toggle the bit
  toggleRegisterBit(outReg, bit);
}


/**
 * Used to read the level of a pin 
 * 
 * @param uint8_t pin   The pin to read 
 * @return uint8_t      The level of the pin (HIGH or LOW)
 */
uint8_t readPin(uint8_t pin)
{
  uint8_t port = getPinPort(pin); 
  uint8_t bit = getPinBit(pin); 

  if (port == NO_PORT) return LOW; // Can't read

  vuint8_t *inReg = getInReg(port); 

  // Return HIGH if the bit is high
  if ((*inReg & bit)) 
    return HIGH; 
  else 
    return LOW;
}