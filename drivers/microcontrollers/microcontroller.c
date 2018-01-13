/**
 * Implementation of generic microcontroller stuff
 *
 * Author: Michael Rouse
 */
#include "microcontroller.h"


/**
 * Used to mark a pin as INPUT or OUTPUT
 *
 * @param io_pin pin      The pin to change the mode of
 * @param pin_mode mode   The mode (INPUT or OUTPUT)
 */
void setPinMode(io_pin pin, pin_mode mode)
{
  uint8_t port;
  uint8_t bit;
  vuint8_t *reg;

  // Get the port and bit
  getPinPort(port, pin);
  getPinBit(bit, pin);

  // Get the dir register
  getDirReg(reg, port);

  // Set the pin mode
  if (mode == INPUT) {
    // INPUT
    setRegisterBitLow(reg, bit);
  }
  else if (mode == OUTPUT) {
    // OUTPUT
    setRegisterBitHigh(reg, bit);
  }
  else if (mode == Interrupt) {
    // INTERRUPT
    setInput(pin); // Mark Pin as INPUT

    // Configure interrupt registers
    getIESReg(reg, port);
    setRegisterBitHigh(reg, bit);

    getIFGReg(reg, port);
    setRegisterBitLow(reg, bit);

    getIEReg(reg, port);
    setRegisterBitHigh(reg, bit);
  }
}


/**
 * Used to set a pin HIGH or LOW
 *
 * @param io_pin pin        The pin to change the state of
 * @param pin_level level   The new pin state, HIGH or LOW
 */
void setPinLevel(io_pin pin, pin_level level)
{
  uint8_t port;
  uint8_t bit;
  vuint8_t *outReg;

  // Get port and bit
  getPinPort(port, pin);
  getPinBit(bit, pin);

  // Get out register
  getOutReg(outReg, port);

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
 * @param io_pin pin   The pin to toggle
 */
void togglePinLevel(io_pin pin)
{
  uint8_t port;
  uint8_t bit;
  vuint8_t *outReg;

  getPinPort(port, pin);
  getPinBit(bit, pin);
  getOutReg(outReg, port);

  // Toggle the bit
  toggleRegisterBit(outReg, bit);
}


/**
 * Used to read the level of a pin
 *
 * @param io_pin pin    The pin to read
 * @return pin_level      The level of the pin (HIGH or LOW)
 */
pin_level readPin(io_pin pin)
{
  uint8_t port;
  uint8_t bit;
  vuint8_t *inReg;

  getPinPort(port, pin, LOW);
  getPinBit(bit, pin, LOW);
  getInReg(inReg, port, LOW);


  // Return HIGH if the bit is high
  if ((*inReg & bit))
    return HIGH;
  else
    return LOW;
}

