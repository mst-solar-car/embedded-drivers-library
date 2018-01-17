/**
 * MCP2515 CAN Controller Header
 *
 * Authors: Michael Rouse
 */
#ifndef CAN_CONTROLLER
#define CAN_CONTROLLER

#include "../can_controller.h"



/**
 * Functions specific to the MCP2515 Driver
 */
void _mcp2515_write(uint8_t addr, uint8_t* buff, uint8_t bytes);
void _mcp2515_modify(uint8_t addr, uint8_t mask, uint8_t data);
void _mcp2515_read(uint8_t addr, uint8_t* out, uint8_t bytes);
void _mcp2515_reset(void);
void _mcp2515_request_send(void);
bool _mcp2515_is_busy(void);
uint8_t _mcp2515_read_status(void);
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

#define MCP2515_TXRTSCTRL_REGISTER  0x0D  // Register for configuration of the TXnRTS pins

#define EFLAG           0x2D
#define TEC             0x1C
#define REC             0x1D




#endif