/**
 * This file should contain user configuration needed for the drivers
 *
 * You should not alter any other .h files for these drivers.
 */
#ifndef USER_CONFIG
#define USER_CONFIG


/*******************************
 *      CAN Configuration      *
 *******************************/

// Change these filters to be the Message IDs that this board should receive
#define CAN_FILTER1         0x100
#define CAN_FILTER2         0x200
#define CAN_FILTER3         0x300
#define CAN_FILTER4         0x400
#define CAN_FILTER5         0x600
#define CAN_FILTER6         0x700

// Adjust these masks so IDs can be checked against the filters (0x000 will make a match with any filter)
#define CAN_MASK1           0x000
#define CAN_MASK2           0x000


#endif