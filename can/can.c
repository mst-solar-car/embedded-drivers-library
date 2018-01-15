/**
 * CAN Driver Implementation
 *
 * Author: Michael Rouse
 */
#include "can.h"


/**
 * "Public" Variables
 */
can_message* can_new_msg;


/**
 * "Private" Variables (for this file only)
 */
static can_message _tx_queue[CAN_BUFFER_LENGTH];
static can_message* _tx_push;
static can_message* _tx_pop;

static can_message _rx_queue[CAN_BUFFER_LENGTH];
static can_message* _rx_push;
static can_message* _rx_pop;

static io_pin   _can_int_pin;


/**
 * Initializes the CAN Driver
 */
void can_setup(io_pin cs_pin, io_pin int_pin)
{
  _can_int_pin = int_pin;

#ifndef NO_INTERRUPTS
  // Configure pin for interrupts
  attachInterrupt(_can_int_pin, can_message_check);
#endif

  // Configure queues
  _tx_push = _tx_queue;
  _tx_pop = _tx_push;

  _rx_push = _rx_queue;
  _rx_pop = _rx_push;

  // Initialize user access variable
  can_new_msg = _tx_push;

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
  // Check for any missed interrupts or whatever
  //can_message_check();

  // If pointers are equal then no new messages
  if (_rx_push == _rx_pop)
    return (can_message*)NOTHING;

  // New messages! Get the message from the front of the queue
  can_message* msg = _rx_pop;

  // Advance the pop pointer
  _rx_pop++;
  if (_rx_pop >= (_rx_queue + CAN_BUFFER_LENGTH))
    _rx_pop = _rx_queue; // Reset

  if (msg->address == 0x00)
    return (can_message*)NOTHING;

  return msg;
}


/**
 * Send a CAN Message
 */
bool can_transmit(void)
{
  uint8_t i;
  can_message* tx_push_old = _tx_push;

  // Increase push pointer before anything
  _tx_push++;
  if (_tx_push >= (_tx_queue + CAN_BUFFER_LENGTH))
    _tx_push = _tx_queue;

  // Reset contents of new can message
  _tx_push->address = NULL;
  _tx_push->status = CAN_OK;
  for (i = 0; i < 8; i++) _tx_push->data.data_u8[i] = NULL;

  can_new_msg = _tx_push; // Update variable for programmer to use

  // Send messages in the queue
  //uint8_t loop_count = 0;
  while (_tx_pop != tx_push_old) {
    // Stop sending if the bus is busy
    if (_tx_pop->address != 0x00)
      if (!can_controller_transmit(_tx_pop))
        return Failure;

    // Advance the queue
    _tx_pop++;
    if (_tx_pop >= (_tx_queue + CAN_BUFFER_LENGTH))
      _tx_pop = _tx_queue;

    /*if (loop_count >= 254)
        break;
    loop_count++;*/
  }

  // Check for any missed messages
 //can_message_check();

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
void can_message_check(void)
{
  // Check if interrupt was missed
  while(readPin(_can_int_pin) == Low) {
    // Interrupt was missed
    _can_handle_receiving_message();
  }
}








/**
 * "Private" Functions
 * These functions should only be called from inside solarcar_can.c
 */


/**
 * This function is further implementation of the can_message_check() function
 */
void _can_handle_receiving_message(void)
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
