/**
 * CAN Driver Implementation
 *
 * Authors: Michael Rouse
 */
#include "can.h"

// Transmit Queue
can_message _tx_queue[CAN_BUFFER_LENGTH];
can_message* _tx_push_ptr;
can_message* _tx_pop_ptr;

// Receive Queue
can_message _rx_queue[CAN_BUFFER_LENGTH];
can_message* _rx_push_ptr;
can_message* _rx_pop_ptr;




/**
 * Initializes the CAN Driver
 */
void can_setup()
{
  // Configure the interrupt pin if set to use interrupts
  #ifdef CAN_ENABLE_INTERRUPTS
  setInput(CAN_INTERRUPT_PIN);
  ies(CAN_INTERRUPT_PIN) |= bit(CAN_INTERRUPT_PIN);   // Set edge select
  ifg(CAN_INTERRUPT_PIN) &= ~bit(CAN_INTERRUPT_PIN);  // Set interrupt flag
  ie(CAN_INTERRUPT_PIN) |= bit(CAN_INTERRUPT_PIN);    // Enable as an interrupt
  #endif

  // Configure Pins
  setOutput(CAN_CS_PIN);

  // Setup queues and push/pop pointers
  _tx_push_ptr = _tx_queue;
  _tx_pop_ptr = _tx_push_ptr;

  _rx_push_ptr = _rx_queue;
  _rx_pop_ptr = _rx_push_ptr;

  // Setup the CAN Controller
  can_controller_setup();
}


/**
 * Receives a CAN Message
 *
 * @return can_message*   The message received
 */
can_message* can_receive(void)
{
  // Return nothing if there are no CAN messages
  if (_rx_push_ptr == _rx_pop_ptr) return NO_CAN_MESSAGE;

  // Get message from front of the queue
  can_message* msg = _rx_pop_ptr;

  // Advance the RX pop pointer
  _rx_pop_ptr++;
  if (_rx_pop_ptr == (_rx_queue + CAN_BUFFER_LENGTH)) {
    _rx_pop_ptr = _rx_queue;
  }

  return msg;
}


/**
 * Send a CAN Message
 *
 * @param can_message* msg  The message to send, if NULL it will send whatever is the TX queue
 */
int8_t can_transmit(can_message* msg)
{
  // Copy message and put in in the transmit queue
  if (msg != NULL) {
    _tx_push_ptr->address = msg->address;
    _tx_push_ptr->status = msg->status;
    _tx_push_ptr->data.data_u8[0] = msg->data.data_u8[0];
    _tx_push_ptr->data.data_u8[1] = msg->data.data_u8[1];
    _tx_push_ptr->data.data_u8[2] = msg->data.data_u8[2];
    _tx_push_ptr->data.data_u8[3] = msg->data.data_u8[3];
    _tx_push_ptr->data.data_u8[4] = msg->data.data_u8[4];
    _tx_push_ptr->data.data_u8[5] = msg->data.data_u8[5];
    _tx_push_ptr->data.data_u8[6] = msg->data.data_u8[6];
    _tx_push_ptr->data.data_u8[7] = msg->data.data_u8[7];

    // Push to the tx queue
    _tx_push_ptr++;
    if (_tx_push_ptr == (_tx_queue + CAN_BUFFER_LENGTH)) _tx_push_ptr = _tx_queue;
  }

  // Send all the messages in the queue
  while (_tx_pop_ptr != _tx_push_ptr) {
    // Stop trying to send if the bus is busy
    if (!can_controller_transmit(_tx_pop_ptr))
      return CAN_TX_BUSY;

    // Advance the queue
    _tx_pop_ptr++;
    if (_tx_pop_ptr == (_tx_queue + CAN_BUFFER_LENGTH)) _tx_pop_ptr = _tx_queue;
  }

  return CAN_TX_SUCCESS;
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
#ifdef CAN_ENABLE_INTERRUPTS
{
  // Check if the interrupt is from CAN
  if (ifg(CAN_INTERRUPT_PIN) & bit(CAN_INTERRUPT_PIN)) {
    // Interrupt was from CAN
    _can_handle_interrupt();

    // Clear the interrupt
    ifg(CAN_INTERRUPT_PIN) &= ~bit(CAN_INTERRUPT_PIN);

    return TRUE;
  }

  // Check if the interrupt was missed
  if (~readPin(CAN_INTERRUPT_PIN)) {
    // Interrupt was missed
    _can_handle_interrupt();
    return TRUE;
  }

  // Not a CAN interrupt (or no missed interrupts)
  return FALSE;
}
#else
{
  // TODO: do something here
  return FALSE;
}
#endif






/**
 * "Private" Functions
 * These functions should only be called from inside solarcar_can.c
 */


/**
 * This function is further implementation of the can_message_check() function
 */
void _can_handle_interrupt(void)
{
  // Receive the CAN Message into the RX queue
  can_controller_get_message(_rx_push_ptr);

  // Do not actually receive the message if it is marked as an error, no need
  #ifndef CAN_RECEIVE_ERROR_PACKETS
  if (_rx_push_ptr->status == CAN_ERROR) {
    return;
  }
  #endif

  // Advance the RX push pointer
  _rx_push_ptr++;
  if (_rx_push_ptr == (_rx_queue + CAN_BUFFER_LENGTH)) {
    _rx_push_ptr = _rx_queue;
  }
}