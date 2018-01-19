/**
 * CAN Constants
 */
#ifndef __CAN_CONSTANTS_H__
#define __CAN_CONSTANTS_H__

#include "../config.h"

// Probably won't need to change these
#ifndef CAN_BUFFER_LENGTH
#define CAN_BUFFER_LENGTH   32
#endif

// CAN_MESSAGE_SIZE can not be changed
#ifdef CAN_MESSAGE_SIZE
#undef CAN_MESSAGE_SIZE
#endif
#define CAN_MESSAGE_SIZE    13

// CAN Message Statuses
#define CAN_ERROR           0xFFFF
#define CAN_MERROR          0xFFFE
#define CAN_WAKE            0xFFFD
#define CAN_RTR             0xFFFC
#define CAN_OK              0x0001



#endif