/**
 * MCP2515 CAN Controller Header
 *
 * Authors: Michael Rouse
 *
 * This header file is the header for the of the MCP2515 CAN Controller implementation
 * that is compatible with the Solar Car CAN drivers (solarcar_can.h, solarcar_can.c).
 *
 * If another CAN Controller is ever used then new implementation must be written.
 *
 *
 * Some things that that implementation MUST do:
 *
 *    - Define the __SOLARCAR_CAN_CONTROLLER_H__ macro (for including the file),
 *        the GCC compiler will throw an error inside of solarcar_can.h if this is not defined.
 *
 *    - Have the following functions:
 *        void can_controller_setup();
 *        bool can_controller_transmit(can_message* msg);
 *        void can_controller_get_message(can_message* out);
 *
 *        More documentation on these functions can be found below.
 *
 *
 */
#ifndef __SOLARCAR_CAN_CONTROLLER_H__
#define __SOLARCAR_CAN_CONTROLLER_H__

#include "solarcar.h" // Datatypes and stuff


// Enforce certain directives
#ifndef CAN_MESSAGE_SIZE
#error "The CAN_MESSAGE_SIZE directive is not defined, this is pretty important"
#endif

// Enforce filter and mask directives
#ifndef CAN_FILTER1
#error "You must define the CAN_FILTER1 directive in solarcar_can.h"
#endif
#ifndef CAN_FILTER2
#error "You must define the CAN_FILTER2 directive in solarcar_can.h"
#endif
#ifndef CAN_FILTER3
#error "You must define the CAN_FILTER3 directive in solarcar_can.h"
#endif
#ifndef CAN_FILTER4
#error "You must define the CAN_FILTER4 directive in solarcar_can.h"
#endif
#ifndef CAN_FILTER5
#error "You must define the CAN_FILTER5 directive in solarcar_can.h"
#endif
#ifndef CAN_FILTER6
#error "You must define the CAN_FILTER6 directive in solarcar_can.h"
#endif

#ifndef CAN_MASK1
#error "You must define the CAN_MASK1 directive in solarcar_can.h"
#endif
#ifndef CAN_MASK2
#error "You must define the CAN_MASK2 directive in solarcar_can.h"
#endif



/**
 * CAN Controller Setup
 *
 * This function should do all the configuration needed for the CAN Controller
 * to function properly.
 *
 * @param uint16_t* filters         Pointer to array of filters to use
 * @param uint16_t* masks           Pointer to array of masks to use
 */
void can_controller_setup();


/**
 * CAN Controller Transmit
 *
 * This function should send a CAN Message to the CAN Controller and then transmit
 * it on the CAN Bus.
 *
 * @param can_message* msg  The CAN Message to transmit
 * @return bool             True if the message was able to be sent, False if not able to be sent (e.g., CAN was busy)
 */
bool can_controller_transmit(can_message* msg);


/**
 * CAN Controller Get Message
 *
 * Reads the data of a received CAN Message from the MCP2515 and returns it
 * as a pointer to a can_message.
 *
 * @param can_message* out   The message received
 */
void can_controller_get_message(can_message* out);





/**
 * "Private" Functions/Variables
 *
 * Functions/Variables declared below this line are used internally to the
 * MCP2515 driver and not used anywhere else
 */



// Buffer to hold data to be sent to the CAN Controller
extern uint8_t _buffer[CAN_MESSAGE_SIZE];


/**
 * Writes a command to the CAN Controller
 *
 * @param uint8_t   addr    Address of the register to write to
 * @param uint8_t*  buff    Data to send
 * @param uint8_t   bytes   Number of bytes to write
 */
void _mcp2515_write(uint8_t addr, uint8_t* buff, uint8_t bytes);


/**
 * Modifies a register on the CAN Controller
 *
 * @param uint8_t   addr    Address of the register to modify
 * @param uint8_t   mask    Bit mask
 * @param uint8_t   data    New Bit data
 */
void _mcp2515_modify(uint8_t addr, uint8_t mask, uint8_t data);


/**
 * Reads data from the CAN Controller
 *
 * @param uint8_t   addr    Register to read from
 * @param uint8_t*  out     Buffer to save data to
 * @param uint8_t   bytes   Number of bytes to read
 */
void _mcp2515_read(uint8_t addr, uint8_t* out, uint8_t bytes);


/**
 * Resets the MCP2515
 */
void _mcp2515_reset();


/**
 * Tells the CAN Controller to send a message
 *
 */
void _mcp2515_request_send();


/**
 * Checks if CAN is busy
 */
bool _mcp2515_is_busy(void);


/**
 * Returns the status on the MCP2515
 */
uint8_t _mcp2515_read_status();


/**
 * Returns a CAN Message from the specified buffer
 *
 * @param uint8_t       rxbuf     The buffer to read the CAN Message from
 * @param can_message*  out       Pointer to a CAN Message to save data to
 */
void _mcp2515_get_message_from_buffer(uint8_t rxbuf, can_message* out);


/**
 * Commands
 *
 * Directives that make reading the MCP2515 code easier
 */
#define MCP2515_WRITE_CMD         0x02  // Command to write a register
#define MCP2515_READ_CMD          0x03  // Command to read a register
#define MCP2515_WRITE_TX_CMD      0x40  // Command to write a message to transmit
#define MCP2515_READ_RX_CMD       0x90  // Command to read a received message
#define MCP2515_STATUS_CMD        0xA0  // Command to read CAN status
#define MCP2515_MODIFY_CMD        0x05  // Command to modify CAN Controller

#define MCP2515_FLAG_REGISTER     0x2C  // CANINTF - Register that holds Flags
#define MCP2515_RX0_REGISTER      0x60  // RXB0CTRL - Register to hold RX0 message
#define MCP2515_RX1_REGISTER      0x70  // RXB1CTRL - Register to hold RX1 message

#define MCP2515_RX0_CHECK         0x01  // Used to determine if a message is in RX0
#define MCP2515_RX1_CHECK         0x02  // Used to determine if a message is in RX1
#define MCP2515_ERROR_CHECk       0x20  // Used to determine if flags have errors
#define MCP2515_REMOTE_CHECK      0x08  // Used to check if message is remote request frame

#define MCP2515_FILTER1_REGISTER  0x00  // RXF0SIDH - Register for part of the filters
#define MCP2515_FILTER2_REGISTER  0x10  // RXF3SIDH - Register for part of the filters
#define MCP2515_MASK_REGISTER     0x20  // RXM0SIDH - Register for masks


#define EFLAG           0x2D
#define TEC             0x1C
#define REC             0x1D


#endif