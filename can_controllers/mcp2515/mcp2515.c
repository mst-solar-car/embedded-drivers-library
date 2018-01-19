/**
 * MCP2515 CAN Controller Implementation
 *
 * Author: Michael Rouse
 */
#include "mcp2515.h"


// Remember the chip select pin
static io_pin   _can_controller_cs_pin;
static io_pin   _can_controller_int_pin;

// Buffer to hold data to be sent to the CAN Controller
static uint8_t _buffer[CAN_MESSAGE_SIZE+1];

/**
 * "Private" Functions specific to MCP2515
 */
static void _mcp2515_write(uint8_t addr, uint8_t* buff, uint8_t bytes);
static void _mcp2515_modify(uint8_t addr, uint8_t mask, uint8_t data);
static void _mcp2515_read(uint8_t addr, uint8_t* out, uint8_t bytes);
static void _mcp2515_reset(void);
static void _mcp2515_request_send(void);
static bool _mcp2515_is_busy(void);
static uint8_t _mcp2515_read_status(void);
static void _mcp2515_get_message_from_buffer(uint8_t rxbuf, can_message* out);


#ifdef MCP2515_USE_RXBF_PINS
static void _mcp2515_handle_RX0BF_interrupt(void);
static void _mcp2515_handle_RX1BF_interrupt(void);
#else
static void _mcp2515_get_message(can_message* out);
#endif



/**
 * CAN Controller Setup
 *
 * This function should do all the configuration needed for the CAN Controller
 * to function properly.
 */
void can_controller_setup(io_pin cs_pin, io_pin int_pin)
{
  // Setup the CS pin
  _can_controller_cs_pin = cs_pin;
  outputPin(_can_controller_cs_pin);
  setPinHigh(_can_controller_cs_pin);

  // Setup the INT pin
  _can_controller_int_pin = int_pin;
#ifndef MC_NO_INTERRUPTS
#ifndef MCP2515_USE_RXBF_PINS
  // Use only a single interrupt pin
  attachInterrupt(_can_controller_int_pin, can_controller_poll);
#else
  // Use interrupts for RX0BF and RX1BF
  attachInterrupt(MCP2515_RX0BF_PIN, _mcp2515_handle_RX0BF_interrupt);
  attachInterrupt(MCP2515_RX1BF_PIN, _mcp2515_handle_RX1BF_interrupt);
#endif
#endif

  // Configure the CAN Controller
#ifdef MCP2515_RESET_PIN
  outputPin(MCP2515_RESET_PIN);
  setPinHigh(MCP2515_RESET_PIN);
#endif
  _mcp2515_reset();

  // Delay for reset
  uint16_t i;
  for(i = 0; i < 1000; i++);

  // Enter config mode
  _mcp2515_modify(MCP2515_CONTROL_REGISTER, 0x03, 0x00); // TODO: Fix constants

  _buffer[0] = 0x05; // (CNF3) -|
  _buffer[1] = 0xF8; // (CNF2)  |- Configure Baudrate for 500 kbps
  _buffer[2] = 0x00; // (CNF1) -|

#ifndef MCP2515_USE_RXBF_PINS
  _buffer[3] = 0x23; // (CANINTE) enable error, rx0 & rx1 interrupts on IRQ pin
#else
  _buffer[3] = 0x03; // If useing the RXnBF pins then don't do anything with the INT pin
#endif
  _buffer[4] = 0x00; // (CANINTF) register: clear all IRQ flags
  _buffer[5] = 0x00; // (EFLG) clear all user changable error flags
  _mcp2515_write(MCP2515_CNF3_REGISTER, &_buffer[0], 6); // TODO: FIX CONSTANTS

#ifndef MCP2515_NO_ROLLOVER
  _mcp2515_modify(MCP2515_RX0_REGISTER, 0x04, 0x04); // Enable receive buffer rollover
#endif

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

#ifdef MCP2515_USE_RTS_PINS
  // Set function of the RTS pins if configured
  _buffer[0] = 0x01;
  _buffer[1] = 0x01;
  _buffer[2] = 0x01;
  _mcp2515_write(MCP2515_TXRTSCTRL_REGISTER, &_buffer[0], 3); // Sets the function of TX0RTS, TX1RTS, and TX2RTS as a RTS pin

  outputPin(MCP2515_TX0RTS_PIN); // Set mode of pin for the RTS as output
  setPinHigh(MCP2515_TX0RTS_PIN);

  #ifdef MCP2515_TX1RTS_PIN
    outputPin(MCP2515_TX1RTS_PIN);
    setPinHigh(MCP2515_TX1RTS_PIN);
  #endif
  #ifdef MCP2515_TX2RTS_PIN
    outputPin(MCP2515_TX2RTS_PIN);
    setPinHigh(MCP2515_TX2RTS_PIN);
  #endif
#endif

#ifdef MCP2515_USE_RXBF_PINS
  // Configure the RXnBF pin functionality
  _buffer[0] = 0x01;
  _buffer[1] = 0x01;
  _buffer[2] = 0x01;
  _buffer[3] = 0x01;
  _mcp2515_write(MCP2515_BFPCTRL_REGISTER, &_buffer[0], 4);
#endif

  // Leave config mode
  _mcp2515_modify(MCP2515_CONTROL_REGISTER, 0xE0, 0x00); // Leave configuration mode
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
  uint8_t i;

  if (_mcp2515_is_busy() == True) {
    return Failure; // CAN is busy, do not transmit the message
  }

  // Put the message into the buffer
  _buffer[0] = rightShift(msg->address, 3);
  _buffer[1] = leftShift(msg->address, 5);
  _buffer[2] = NULL;  // Extended identifier
  _buffer[3] = NULL;  // Extended identifier
  _buffer[4] = 8;     // Length of data in bytes
  for (i = 0; i < 8; i++)
    _buffer[5+i] = msg->data.data_u8[i]; // Data should start at index 5 in the buffer


  // Transmit the message to the CAN controller
  setPinLow(_can_controller_cs_pin); // Toggle the CS pin
  spi_transmit(DEFAULT_SPI_BUS, MCP2515_LOAD_TX0_CMD);
  for (i = 0; i < CAN_MESSAGE_SIZE; i++) {
    spi_transmit(DEFAULT_SPI_BUS, _buffer[i]);
  }
  setPinHigh(_can_controller_cs_pin); // Untoggle the CS pin

  // Request the CAN Controller sends the message
  _mcp2515_request_send();

  return TRUE;
}


/**
 * This is used to check for missed interrupts, or to poll when you
 * have no interrupts
 */
void can_controller_poll(void)
{
#ifndef MCP2515_USE_RXBF_PINS
  while (readPin(_can_controller_int_pin) == Low) {
    // Interrupt occured
    _mcp2515_get_message(_can_get_next_receive_ptr());
  }

#else
  // Check RX0BF
  _mcp2515_handle_RX0BF_interrupt();

  // Check RX1BF
  _mcp2515_handle_RX1BF_interrupt();
#endif

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
static void _mcp2515_write(uint8_t addr, uint8_t* buff, uint8_t bytes)
{
  uint8_t i;

  setPinLow(_can_controller_cs_pin); // Toggle the CS pin

  spi_transmit(DEFAULT_SPI_BUS, MCP2515_WRITE_CMD);
  spi_transmit(DEFAULT_SPI_BUS, addr);
  for (i = 0; i < (bytes - 1); i++) {
    spi_transmit(DEFAULT_SPI_BUS, *buff++);
  }
  spi_transmit(DEFAULT_SPI_BUS, *buff);

  setPinHigh(_can_controller_cs_pin); // Untoggle the CS pin
}


/**
 * Modifies a register on the CAN Controller
 *
 * @param uint8_t   addr    Address of the register to modify
 * @param uint8_t   mask    Bit mask
 * @param uint8_t   data    New Bit data
 */
static void _mcp2515_modify(uint8_t addr, uint8_t mask, uint8_t data)
{
  setPinLow(_can_controller_cs_pin);

  spi_transmit(DEFAULT_SPI_BUS, MCP2515_MODIFY_CMD);
  spi_transmit(DEFAULT_SPI_BUS, addr);
  spi_transmit(DEFAULT_SPI_BUS, mask);
  spi_transmit(DEFAULT_SPI_BUS, data);

  setPinHigh(_can_controller_cs_pin);
}


/**
 * Reads data from the CAN Controller
 *
 * @param uint8_t   addr    Register to read from
 * @param uint8_t*  out     Buffer to save data to
 * @param uint8_t   bytes   Number of bytes to read
 */
static void _mcp2515_read(uint8_t addr, uint8_t* out, uint8_t bytes)
{
  uint8_t i;

  setPinLow(_can_controller_cs_pin);

  spi_transmit(DEFAULT_SPI_BUS, MCP2515_READ_CMD);
  spi_transmit(DEFAULT_SPI_BUS, addr);

  for (i = 0; i < bytes; i++) {
    *out++ = spi_transmit(DEFAULT_SPI_BUS, NULL); // Transmit nothing to read a value
  }
  setPinHigh(_can_controller_cs_pin);
}


/**
 * Resets the MCP2515
 */
static void _mcp2515_reset()
{
#ifndef MCP2515_RESET_PIN
  // Reset over SPI
  setPinLow(_can_controller_cs_pin);
  spi_transmit(DEFAULT_SPI_BUS, MCP2515_RESET_CMD);
  setPinHigh(_can_controller_cs_pin);
#else
  // Reset using the PIN
  setPinLow(MCP2515_RESET_PIN);
  no_operation();
  setPinHigh(MCP2515_RESET_PIN);
#endif
}


/**
 * Tells the CAN Controller to send a message
 *
 */
static void _mcp2515_request_send()
{
#ifndef MCP2515_USE_RTS_PINS
  // Send RTS signal for TX0RTS over SPI
  uint8_t buff = 0;
  uint8_t i;

  i = 0x80; // TODO: Fix constants specific to MCP2515
  if (buff == 0)
    i |= 0x01;  // TX0RTS
  else if (buff == 1)
    i |= 0x02;  // TX1RTS
  else if (buff == 2)
    i |= 0x04;  // TX2RTS

  // Send Request to Send Command
  setPinLow(_can_controller_cs_pin);
  spi_transmit(DEFAULT_SPI_BUS, i);
  setPinHigh(_can_controller_cs_pin);
#else
  // Send signal for TX0RTS over the TX0RTS pin
  setPinLow(MCP2515_TX0RTS_PIN);
  no_operation();
  setPinHigh(MCP2515_TX0RTS_PIN);
#endif
}


/**
 * Checks if CAN is busy
 */
static bool _mcp2515_is_busy(void)
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
static uint8_t _mcp2515_read_status()
{
  uint8_t status = NULL;

  //P2OUT &= BIT5;
  setPinLow(_can_controller_cs_pin);

  spi_transmit(DEFAULT_SPI_BUS, MCP2515_READ_STATUS_CMD);
  status = spi_transmit(DEFAULT_SPI_BUS, NULL);

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
static void _mcp2515_get_message_from_buffer(uint8_t rxbuf, can_message* out)
{
  uint8_t i;

  // Determine SPI command to send
  uint8_t cmd = MCP2515_READ_RX0_CMD;
  if (rxbuf == MCP2515_RX1_REGISTER)
    cmd = MCP2515_READ_RX1_CMD;

  // Read from the buffer and reset the interrupt pin
  setPinLow(_can_controller_cs_pin);
  spi_transmit(DEFAULT_SPI_BUS, cmd);
  for (i = 0; i <= CAN_MESSAGE_SIZE; i++)
    _buffer[i] = spi_transmit(DEFAULT_SPI_BUS, NULL);
  setPinHigh(_can_controller_cs_pin);

  // Read from the specified RX Buffer
  //_mcp2515_read(rxbuf, &_buffer[0], CAN_MESSAGE_SIZE + 1);

  // Check what type of packet it is
  if ((_buffer[0] & MCP2515_REMOTE_CHECK) == NULL) {
    // Standard data packet
    out->status = CAN_OK;

    // Fill in data
    for (i = 0; i < 8; i++)
      out->data.data_u8[i] = _buffer[6 + i]; // Data starts at _buffer[6]
  }
  else {
    // Remote Frame Request -- Data is irrelevant
    out->status = CAN_RTR;
  }

  // Fill in sender address
  out->address = (_buffer[1] << 3) | (_buffer[2] >> 5); //leftShift(_buffer[1], 3) | rightShift(_buffer[2], 5);
}




/**
 * This is used for handling an interrupt that occured on the RX0BF pin
 */
#ifdef MCP2515_USE_RXBF_PINS
static void _mcp2515_handle_RX0BF_interrupt(void)
{
  // Receive message(s) from the RX0 Buffer
  while (readPin(MCP2515_RX0BF_PIN) == Low)
  {
    _mcp2515_get_message_from_buffer(MCP2515_RX0_REGISTER, _can_get_next_receive_ptr());
    //setPinHigh(MCP2515_RX0BF_PIN);
    //_mcp2515_modify(MCP2515_CANINTF_REGISTER, MCP2515_RX0_CHECK, NULL);
  }
}
#endif


/**
 * This is used for handling an interrupt that occured on the RX1BF pin
 */
#ifdef MCP2515_USE_RXBF_PINS
static void _mcp2515_handle_RX1BF_interrupt(void)
{
  // Receive message(s) from the RX1 Buffer
  while (readPin(MCP2515_RX1BF_PIN) == Low)
  {
    _mcp2515_get_message_from_buffer(MCP2515_RX1_REGISTER, _can_get_next_receive_ptr());
    //setPinHigh(MCP2515_RX1BF_PIN);
    //_mcp2515_modify(MCP2515_CANINTF_REGISTER, MCP2515_RX1_CHECK, NULL);
  }
}
#endif


/**
 * This is used when you don't know what buffer the interrupt came from (only one interrupt pin)
 */
#ifndef MCP2515_USE_RXBF_PINS
static void _mcp2515_get_message(can_message* out)
{
  // Read the flags
  uint8_t flags;
  _mcp2515_read(MCP2515_CANINTF_REGISTER, &flags, 1);

  // Check for errors
  if ((flags & MCP2515_ERROR_CHECK) != NULL) {
    // Error exists...
    out->status = CAN_ERROR;

    _mcp2515_read(EFLAG, &_buffer[0], 1);
    _mcp2515_read(TEC, &_buffer[1], 2);

    // Clear flags
    _mcp2515_modify(EFLAG, _buffer[0], NULL);
    _mcp2515_modify(MCP2515_CANINTF_REGISTER, MCP2515_ERROR_CHECK, NULL);
  }

  // No errors, receive message if it's in RX Buffer 0
  else if ((flags & MCP2515_RX0_CHECK) != NULL) {
    // Read CAN Message
    _mcp2515_get_message_from_buffer(MCP2515_RX0_REGISTER, out);

    // Clear flags
    //_mcp2515_modify(MCP2515_CANINTF_REGISTER, MCP2515_RX0_CHECK, NULL);
  }

  // Receive message if it's in RX Buffer 1
  else if ((flags & MCP2515_RX1_CHECK) != NULL) {
    // Read CAN Message
    _mcp2515_get_message_from_buffer(MCP2515_RX1_REGISTER, out);

    // Clear flags
    //_mcp2515_modify(MCP2515_CANINTF_REGISTER, MCP2515_RX1_CHECK, NULL);
  }
}
#endif
