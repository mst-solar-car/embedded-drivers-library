/**
 * MCP2515 CAN Controller Implementation
 *
 * Author: Michael Rouse
 */
#include "mcp2515.h"


// Remember the chip select pin
io_pin _can_controller_cs_pin;

// Buffer to hold data to be sent to the CAN Controller
uint8_t _buffer[CAN_MESSAGE_SIZE+1];


/**
 * CAN Controller Setup
 *
 * This function should do all the configuration needed for the CAN Controller
 * to function properly.
 */
void can_controller_setup(io_pin cs_pin)
{
  // Setup the CS pin
  outputPin(cs_pin);
  setPinHigh(cs_pin);
  _can_controller_cs_pin = cs_pin;

  // Configure the CAN Controller
  _mcp2515_reset();

  // Delay for reset
  uint16_t i;
  for(i = 0; i < 1000; i++);

  // Enter config mode
  _mcp2515_modify(0x0F, 0x03, 0x00); // TODO: Fix constants

  _buffer[0] = 0x05;
  _buffer[1] = 0xF8;
  _buffer[2] = 0x00;

  _buffer[3] = 0x23;
  _buffer[4] = 0x00;
  _buffer[5] = 0x00;
  _mcp2515_write(0x28, &_buffer[0], 6); // TODO: FIX CONSTANTS

  // TODO: Receive buffer rollover
  _mcp2515_modify(0x60, 0x04, 0x04);

  // First set of filters
  _buffer[0] = rightShift(CAN_FILTER1, 3);
  _buffer[1] = leftShift(CAN_FILTER1, 5);
  _buffer[2] = NULL;
  _buffer[3] = NULL;

  _buffer[4] = rightShift(CAN_FILTER2, 3);
  _buffer[5] = leftShift(CAN_FILTER2, 5);
  _buffer[6] = NULL;
  _buffer[7] = NULL;

  _buffer[8] = rightShift(CAN_FILTER3, 3);
  _buffer[9] = leftShift(CAN_FILTER3, 5);
  _buffer[10] = NULL;
  _buffer[11] = NULL;
  _mcp2515_write(MCP2515_FILTER1_REGISTER, &_buffer[0], 12);

  // Second set of filters
  _buffer[0] = rightShift(CAN_FILTER4, 3);
  _buffer[1] = leftShift(CAN_FILTER4, 5);
  _buffer[2] = NULL;
  _buffer[3] = NULL;

  _buffer[4] = rightShift(CAN_FILTER5, 3);
  _buffer[5] = leftShift(CAN_FILTER5, 5);
  _buffer[6] = NULL;
  _buffer[7] = NULL;

  _buffer[8] = rightShift(CAN_FILTER6, 3);
  _buffer[9] = leftShift(CAN_FILTER6, 5);
  _buffer[10] = NULL;
  _buffer[11] = NULL;
  _mcp2515_write(MCP2515_FILTER2_REGISTER, &_buffer[0], 12);

  // Masks
  _buffer[0] = rightShift(CAN_MASK1, 3);
  _buffer[1] = leftShift(CAN_MASK1, 5);
  _buffer[2] = NULL;
  _buffer[3] = NULL;

  _buffer[4] = rightShift(CAN_MASK2, 3);
  _buffer[5] = leftShift(CAN_MASK2, 5);
  _buffer[6] = NULL;
  _buffer[7] = NULL;
  _mcp2515_write(MCP2515_MASK_REGISTER, &_buffer[0], 8);

  // Leave config mode
  _mcp2515_modify(0x0F, 0xE0, 0x00); // Leave configuration mode
}



/**
 * CAN Controller Transmit
 *
 * This function should send a CAN Message to the CAN Controller and then transmit
 * it on the CAN Bus.
 *
 * @param can_message* msg  The CAN Message to transmit
 * @return bool             True if the message was able to be sent, False if not able to be sent (e.g., CAN was busy)
 */
bool can_controller_transmit(can_message* msg)
{
  if (_mcp2515_is_busy() == TRUE) {
    return FALSE; // CAN is busy, do not transmit the message
  }

  // Put the message into the buffer
  _buffer[0] = rightShift(msg->address, 3);
  _buffer[1] = leftShift(msg->address, 5);
  _buffer[2] = NULL;  // Extended identifier
  _buffer[3] = NULL;  // Extended identifier
  _buffer[4] = 8;     // Length of data in bytes
  _buffer[5] = msg->data.data_u8[0];
  _buffer[6] = msg->data.data_u8[1];
  _buffer[7] = msg->data.data_u8[2];
  _buffer[8] = msg->data.data_u8[3];
  _buffer[9] = msg->data.data_u8[4];
  _buffer[10] = msg->data.data_u8[5];
  _buffer[11] = msg->data.data_u8[6];
  _buffer[12] = msg->data.data_u8[7];

  uint8_t i;

  // Transmit the message to the CAN controller
  setPinLow(_can_controller_cs_pin); // Toggle the CS pin
  spi_transmit(MCP2515_WRITE_TX_CMD);
  for (i = 0; i < CAN_MESSAGE_SIZE; i++) {
    spi_transmit(_buffer[i]);
  }
  setPinHigh(_can_controller_cs_pin); // Untoggle the CS pin

  // Request the CAN Controller sends the message
  _mcp2515_request_send();

  return TRUE;
}


/**
 * CAN Controller Get Message
 *
 * Reads the data of a received CAN Message from the MCP2515 and returns it
 * as a pointer to a can_message.
 *
 * @param can_message* out   The message received
 */
void can_controller_get_message(can_message* out)
{
  // Read the flags
  uint8_t flags;
  _mcp2515_read(MCP2515_FLAG_REGISTER, &flags, 1);

  // Check for errors
  if ((flags & MCP2515_ERROR_CHECk) != NULL) {
    // Error exists...
    out->status = CAN_ERROR;

    _mcp2515_read(EFLAG, &_buffer[0], 1);
    _mcp2515_read(TEC, &_buffer[1], 2);

    // Clear flags
    _mcp2515_modify(EFLAG, _buffer[0], NULL);
    _mcp2515_modify(MCP2515_FLAG_REGISTER, MCP2515_ERROR_CHECk, NULL);
  }

  // No errors, receive message if it's in RX Buffer 0
  else if ((flags & MCP2515_RX0_CHECK) != NULL) {
    // Read CAN Message
    _mcp2515_get_message_from_buffer(MCP2515_RX0_REGISTER, out);

    // Clear flags
    _mcp2515_modify(MCP2515_FLAG_REGISTER, MCP2515_RX0_CHECK, NULL);
  }

  // Receive message if it's in RX Buffer 1
  else if ((flags & MCP2515_RX1_CHECK) != NULL) {
    // Read CAN Message
    _mcp2515_get_message_from_buffer(MCP2515_RX1_REGISTER, out);

    // Clear flags
    _mcp2515_modify(MCP2515_FLAG_REGISTER, MCP2515_RX1_CHECK, NULL);
  }

  return;
}






/**
 * "Private" Functions
 */


/**
 * Writes a command to the CAN Controller
 *
 * @param uint8_t   addr    Address of the register to write to
 * @param uint8_t*  buff    Data to send
 * @param uint8_t   bytes   Number of bytes to write
 */
void _mcp2515_write(uint8_t addr, uint8_t* buff, uint8_t bytes)
{
  uint8_t i;

  setPinLow(_can_controller_cs_pin); // Toggle the CS pin

  spi_transmit(MCP2515_WRITE_CMD);
  spi_transmit(addr);
  for (i = 0; i < (bytes - 1); i++) {
    spi_transmit(*buff++);
  }
  spi_transmit(*buff);

  setPinHigh(_can_controller_cs_pin); // Untoggle the CS pin
}


/**
 * Modifies a register on the CAN Controller
 *
 * @param uint8_t   addr    Address of the register to modify
 * @param uint8_t   mask    Bit mask
 * @param uint8_t   data    New Bit data
 */
void _mcp2515_modify(uint8_t addr, uint8_t mask, uint8_t data)
{
  setPinLow(_can_controller_cs_pin);

  spi_transmit(MCP2515_MODIFY_CMD);
  spi_transmit(addr);
  spi_transmit(mask);
  spi_transmit(data);

  setPinHigh(_can_controller_cs_pin);
}


/**
 * Reads data from the CAN Controller
 *
 * @param uint8_t   addr    Register to read from
 * @param uint8_t*  out     Buffer to save data to
 * @param uint8_t   bytes   Number of bytes to read
 */
void _mcp2515_read(uint8_t addr, uint8_t* out, uint8_t bytes)
{
  uint8_t i;

  P2OUT &= ~BIT5;

  //setPinLow(_can_controller_cs_pin);

  spi_transmit(MCP2515_READ_CMD);
  spi_transmit(addr);

  for (i = 0; i < bytes; i++) {
    *out++ = spi_transmit(NULL); // Transmit nothing to read a value
  }
P2OUT |= BIT5;
  //setPinHigh(_can_controller_cs_pin);
}


/**
 * Resets the MCP2515
 */
void _mcp2515_reset()
{
  setPinLow(_can_controller_cs_pin);

  spi_transmit(0xC0); // TODO: fix constant

  setPinHigh(_can_controller_cs_pin);
}


/**
 * Tells the CAN Controller to send a message
 *
 */
void _mcp2515_request_send()
{
  uint8_t buff = 0;
  uint8_t i;

  i = 0x80; // TODO: Fix constants specific to MCP2515
  if (buff == 0)
    i |= 0x01;
  else if (buff == 1)
    i |= 0x02;
  else if (buff == 2)
    i |= 0x04;

  // Send Request to Send Command
  setPinLow(_can_controller_cs_pin);
  spi_transmit(i);
  setPinHigh(_can_controller_cs_pin);
}


/**
 * Checks if CAN is busy
 */
bool _mcp2515_is_busy(void)
{
  uint8_t status = _mcp2515_read_status();

  // If bit 4 of the status is high then CAN is busy
  if (isBitHigh(status, 0x04)) {
    return TRUE;
  }

  return FALSE;
}


/**
 * Returns the status on the MCP2515
 */
uint8_t _mcp2515_read_status()
{
  uint8_t status = NULL;

  //P2OUT &= BIT5;
  setPinLow(_can_controller_cs_pin);

  spi_transmit(MCP2515_STATUS_CMD);
  status = spi_transmit(NULL);

  setPinHigh(_can_controller_cs_pin);
  //P2OUT |= BIT5;
  return status;
}


/**
 * Returns a CAN Message from the specified buffer
 *
 * @param uint8_t       rxbuf     The RX Buffer to read the CAN Message from
 * @param can_message*  out       Pointer to a CAN Message to save data to
 */
void _mcp2515_get_message_from_buffer(uint8_t rxbuf, can_message* out)
{
  // Read from the specified RX Buffer
  _mcp2515_read(rxbuf, &_buffer[0], CAN_MESSAGE_SIZE + 1);

  // Check what type of packet
  if ((_buffer[0] & MCP2515_REMOTE_CHECK) == NULL) {
    // Standard data packet
    out->status = CAN_OK;

    // Fill in data
    out->data.data_u8[0] = _buffer[6];
    out->data.data_u8[1] = _buffer[7];
    out->data.data_u8[2] = _buffer[8];
    out->data.data_u8[3] = _buffer[9];
    out->data.data_u8[4] = _buffer[10];
    out->data.data_u8[5] = _buffer[11];
    out->data.data_u8[6] = _buffer[12];
    out->data.data_u8[7] = _buffer[13];
  }
  else {
    // Remote Frame Request -- Data is irrelevant
    out->status = CAN_RTR;
  }

  // Fill in sender address
  out->address = (_buffer[1] << 3) | (_buffer[2] >> 5); //leftShift(_buffer[1], 3) | rightShift(_buffer[2], 5);
}



