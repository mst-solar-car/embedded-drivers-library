/**
 * CAN Constants
 */
#ifndef __CAN_CONSTANTS_H__
#define __CAN_CONSTANTS_H__

// Probably won't need to change these
#define CAN_BUFFER_LENGTH   32
#define CAN_MESSAGE_SIZE    13

// CAN Message Statuses
#define CAN_ERROR           0xFFFF
#define CAN_MERROR          0xFFFE
#define CAN_WAKE            0xFFFD
#define CAN_RTR             0xFFFC
#define CAN_OK              0x0001



#endif