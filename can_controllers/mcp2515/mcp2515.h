/**
 * MCP2515 CAN Controller Header
 *
 * Authors: Michael Rouse
 */
#ifndef CAN_CONTROLLER
#define CAN_CONTROLLER

#include "../can_controller.h"

/**
 * Commands
 *
 * Enums to make reading code for the MCP2515 easier.
 *
 * These are pulled straight from the datasheet
 */
#define MCP2515_WRITE_CMD     0x02
#define MCP2515_READ_CMD      0x03
#define MCP2515_MODIFY_CMD    0x05
#define MCP2515_LOAD_TX0_CMD  0x40
#define MCP2515_LOAD_TX1_CMD  0x42
#define MCP2515_LOAD_TX2_CMD  0x44
#define MCP2515_RTS_TX0_CMD   0x81
#define MCP2515_RTS_TX1_CMD   0x82
#define MCP2515_RTS_TX2_CMD   0x84
#define MCP2515_RTS_ALL_CMD   0x87
#define MCP2515_READ_RX0_CMD  0x90
#define MCP2515_READ_RX1_CMD  0x94
#define MCP2515_RESET_CMD     0xC0
#define MCP2515_RX_STATUS_CMD 0xB0

#define MCP2515_READ_STATUS_CMD   0xA0


#define MCP2515_CONTROL_REGISTER    0x0F
#define MCP2515_RX0_REGISTER        0x60  // RXB0CTRL - Register to hold RX0 message
#define MCP2515_RX1_REGISTER        0x70  // RXB1CTRL - Register to hold RX1 message
#define MCP2515_TXRTSCTRL_REGISTER  0x0D  // Register for configuration of the TXnRTS pins
#define MCP2515_FILTER1_REGISTER    0x00  // RXF0SIDH - Register for part of the filters
#define MCP2515_FILTER2_REGISTER    0x10  // RXF3SIDH - Register for part of the filters
#define MCP2515_MASK_REGISTER       0x20  // RXM0SIDH - Register for masks
#define MCP2515_CNF3_REGISTER       0x28
#define MCP2515_CNF2_REGISTER       0x29
#define MCP2515_CNF1_REGISTER       0x2A
#define MCP2515_CANINTE_REGISTER    0x2B  // Interrupt config register
#define MCP2515_CANINTF_REGISTER    0x2C  // Holds flags
#define MCP2515_EFLG_REGISTER       0x2D  // Error flags
#define MCP2515_BFPCTRL_REGISTER    0x0C



#define MCP2515_RX0_CHECK         0x01  // Used to determine if a message is in RX0
#define MCP2515_RX1_CHECK         0x02  // Used to determine if a message is in RX1
#define MCP2515_ERROR_CHECK       0x20  // Used to determine if flags have errors
#define MCP2515_REMOTE_CHECK      0x08  // Used to check if message is remote request frame



#define EFLAG           0x2D
#define TEC             0x1C
#define REC             0x1D





/**
 * Verify configuration directives
 */
#ifdef MCP2515_USE_RTS_PINS
  #ifndef MCP2515_TX0RTS_PIN
    #error "MCP2515 is configured to use RTS pins, but the directive 'MCP2515_TX0RTS_PIN' is not defined in user_config.h"
  #endif
  #ifndef MCP2515_TX1RTS_PIN
    #warning "MCP2515 is configured to use RTS pins, but the directive 'MCP2515_TX1RTS_PIN' is not defined in user_config.h"
  #endif
  #ifndef MCP2515_TX2RTS_PIN
    #warning "MCP2515 is configured to use RTS pins, but the directive 'MCP2515_TX2RTS_PIN' is not defined in user_config.h"
  #endif
#else
  #warning "MCP2515 drivers are using SPI to send RTS commands. Try using the TX0RTS, TX1RTS, and TX2RTS pins"
#endif

// Verify directives for using RXnBF pins
#ifdef MCP2515_USE_RXBF_PINS
  #ifndef MCP2515_RX0BF_PIN
    #error "MCP2515 is configured to use RXnBF pins but the 'MCP2515_RX0BF_PIN' directive is not defined in user_config.h"
  #endif
  #ifndef MCP2515_RX1BF_PIN
    #error "MCP2515 is configured to use RXnBF pins but the 'MCP2515_RX1BF_PIN' directive is not defined in user_config.h"
  #endif
#else
  #warning "MCP2515 drivers are using a single interrupt pins to receive messages from RX0 and RX1 buffers, try using the RX0BF and RX1BF pins"
#endif


#endif
