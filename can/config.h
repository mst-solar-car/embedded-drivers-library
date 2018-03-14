/**
 * CAN Driver Configuration
 *
 * Authors: Everyone?
 */
#ifndef __CAN_CONFIG__
#define __CAN_CONFIG__


enum {
    CAN_DATA_LENGTH     = 8,

    CAN_DEFAULT_FILTER  = 0x0000,
    CAN_DEFAULT_MASK    = 0x7FF
};

#endif