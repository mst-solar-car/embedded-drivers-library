/**
 * Implementation of generic microcontroller stuff
 *
 * Author: Michael Rouse
 */
#include "importer.h"


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

  getPinPort(port, pin);
  getPinBit(bit, pin);
  getDirReg(reg, port);

  // Set the pin mode
  if (mode == Input)
    setRegisterBitLow(reg, bit); // Input
  else
    setRegisterBitHigh(reg, bit); // Output
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

  getPinPort(port, pin);
  getPinBit(bit, pin);
  getOutReg(outReg, port);

  if (level == Low)
    setRegisterBitLow(outReg, bit);
  else
    setRegisterBitHigh(outReg, bit);
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
 * @return pin_level    The level of the pin (HIGH or LOW)
 */
pin_level readPin(io_pin pin)
{
  uint8_t port;
  uint8_t bit;
  vuint8_t *inReg;

  getPinPort(port, pin, Low);
  getPinBit(bit, pin, Low);
  getInReg(inReg, port, Low);

  // Return HIGH if the bit is high
  if (isBitHigh(*inReg, bit))
    return High;
  else
    return Low;
}


// Function for default interrupt (does nothing)
static void emptyFunc(void) { }

static volatile voidFuncPtr _interruptEvents[MC_NUM_INTERRUPTABLE_PORTS][8] = {
#if MC_NUM_INTERRUPTABLE_PORTS > 8
  #warning "More than 8 interruptable ports, some callbacks will not be initialized"
  {emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc},
#endif
#if MC_NUM_INTERRUPTABLE_PORTS > 7
  {emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc},
#endif
#if MC_NUM_INTERRUPTABLE_PORTS > 6
  {emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc},
#endif
#if MC_NUM_INTERRUPTABLE_PORTS > 5
  {emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc},
#endif
#if MC_NUM_INTERRUPTABLE_PORTS > 4
  {emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc},
#endif
#if MC_NUM_INTERRUPTABLE_PORTS > 3
  {emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc},
#endif
#if MC_NUM_INTERRUPTABLE_PORTS > 2
  {emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc},
#endif
#if MC_NUM_INTERRUPTABLE_PORTS > 1
  {emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc},
#endif
#if MC_NUM_INTERRUPTABLE_PORTS > 0
  {emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc, emptyFunc}
#endif
};



/**
 * Used to attach an interrupt to a certain pin
 *
 * @param io_pin  pin         The pin the interrupt should occur on
 * @param void(*func)(void)   Function that should be called when the interrupt occurs
 */
void attachInterrupt(io_pin pin, void(*func)(void))
{
  uint8_t port;
  uint8_t bit;
  vuint8_t *reg;

  inputPin(pin); // Mark Pin as INPUT

  // Get PORT and BIT
  getPinPort(port, pin);
  getPinBit(bit, pin);

  // Configure interrupt registers
  getIESReg(reg, port);
  setRegisterBitHigh(reg, bit);
  getIFGReg(reg, port);
  setRegisterBitLow(reg, bit);
  getIEReg(reg, port);
  setRegisterBitHigh(reg, bit);

  // Add to the list of interrupts
  uint8_t number_bit;
  _numberBit(number_bit, bit);

  _interruptEvents[port][number_bit] = func;
}

// Directive to assist in typing out long and boring stuff
#define intBitCheck(reg, bit) if (isBitHigh(*reg, BIT ## bit)) { _interruptEvents[port][bit](); setRegisterBitLow(reg, BIT ## bit); }

/**
 * This function occurs when there is an interrupt on a pin
 * It will call a user defined function if one has been specified
 */
void _dispatchInterrupt(uint8_t vector, uint8_t port)
#ifndef MC_NO_INTERRUPTS
{
  //interrupts_disable(); // Disable interrupts
  vuint8_t* ifgReg;
  getIFGReg(ifgReg, port);

  // Perform operation based on what bit was toggled in the IFG register
  //intBitCheck(ifgReg, 7)
  intBitCheck(ifgReg, 6)
  else intBitCheck(ifgReg, 5)
  else intBitCheck(ifgReg, 4)
  else intBitCheck(ifgReg, 3)
  else intBitCheck(ifgReg, 2)
  else intBitCheck(ifgReg, 1)
  else intBitCheck(ifgReg, 0)

 // interrupts_enable(); // Re-enable interrupts before leaving ISR
}
#else
{
  // Empty function
}
#endif

