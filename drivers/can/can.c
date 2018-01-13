/**
 * CAN Driver Implementation
 *
 * Author: Michael Rouse
 */
#include "can.h"


// Create message queues
can_message _tx_queue[CAN_BUFFER_LENGTH];
can_message* _tx_push;
can_message* _tx_pop;

can_message _rx_queue[CAN_BUFFER_LENGTH];
can_message* _rx_push;
can_message* _rx_pop;

io_pin _can_int_pin;




/**
 * Initializes the CAN Driver
 */
void can_setup(io_pin cs_pin, io_pin int_pin)
{
  // Configure the interrupt on the chip
  _can_int_pin = int_pin;
  setInterrupt(_can_int_pin);

  // Configure queues
  _tx_push = _tx_queue;
  _tx_pop = _tx_push;

  _rx_push = _rx_queue;
  _rx_pop = _rx_push;

  // Setup the CAN Controller
  can_controller_setup(cs_pin);
}


/**
 * Receives a CAN Message
 *
 * @return can_message*   The message received
 */
can_message* can_receive(void)
{
  if (_rx_push == _rx_pop) return NOTHING;

  // Get the message from the front of the queue
  can_message* msg = _rx_pop;

  // Advance the pop pointer
  _rx_pop++;
  if (_rx_pop == (_rx_queue + CAN_BUFFER_LENGTH))
    _rx_pop = _rx_queue; // Reset

  return msg;
}


/**
 * Send a CAN Message
 *
 * @param can_message* msg  The message to send, if NULL it will send whatever is the TX queue
 */
bool can_transmit(can_message* msg)
{
  // Copy message to queue if given
  if (msg != NOTHING) {
    _tx_push->address = msg->address;
    _tx_push->status = msg->status;

    // Copy over all of the data
    uint8_t i;
    for (i = 0; i < 8; i++)
      _tx_push->data.data_u8[i] = msg->data.data_u8[i];

    // Push to queue
    _tx_push++;
    if (_tx_push == (_tx_queue + CAN_BUFFER_LENGTH))
      _tx_push = _tx_queue; // Reset
  }

  // Send all messages in the queue
  while (_tx_pop != _tx_push) {
    // Stop sending if the bus is busy
    if (!can_controller_transmit(_tx_pop))
      return Failure;

    // Advance the queue
    _tx_pop++;
    if (_tx_pop == (_tx_queue + CAN_BUFFER_LENGTH))
      _tx_pop = _tx_queue; // Reset
  }

  return Success;
}


/**
 * Checks if the interrupt that occured was for CAN, and if it was it will receive the message
 * If you are using interrupts, then call this function when the port interrupt occurs.
 *
 * This can also be used to check if an interrupt was missed (by calling it in the main loop)
 *
 * @return bool   TRUE if the interrupt was CAN and was handled, FALSE otherwise
 */
bool can_message_check(void)
{
  uint8_t port;
  uint8_t bit;
  vuint8_t* ifgReg;

  // Get port, bit, and register values for interrupt checking
  getPinPort(port, _can_int_pin, False);
  getPinBit(bit, _can_int_pin, False);
  getIFGReg(ifgReg, port, False);

  // Check if interrupt flag is set for CAN
  if (isHigh(*ifgReg, bit)) {
    // Interrupt was from CAN
    _can_handle_interrupt();

    setRegisterBitLow(ifgReg, bit); // Clear flag

    return True;
  }

  // Check if interrupt was missed
  if (~readPin(_can_int_pin)) {
    // Interrupt was missed
    _can_handle_interrupt();

    return True;
  }

  return False; // Not a CAN interrupt (or no missed interrupt)
}







/**
 * "Private" Functions
 * These functions should only be called from inside solarcar_can.c
 */


/**
 * This function is further implementation of the can_message_check() function
 */
void _can_handle_interrupt(void)
{
  // Receive a CAN Message into the RX queue
  can_controller_get_message(_rx_push);

  // If message is an error, ignore it
  #ifndef CAN_RECEIVE_ERROR_PACKETS
  if (_rx_push->status == CAN_ERROR)
    return;
  #endif

  // Advance the rx push pointer to the next spot
  _rx_push++;
  if (_rx_push == (_rx_queue + CAN_BUFFER_LENGTH))
    _rx_push = _rx_queue;
}
