/**
 * CAN Driver Configuration
 *
 * Authors: Everyone?
 */
#ifndef __CAN_CONFIG__
#define __CAN_CONFIG__


/**
 * Pre-defined Masks and Filters
 */
#define CAN_MASK_ALL_IDS        0x000   // Accepts all IDS (filters don't matter)
#define CAN_MASK_EXACT_IDS      0x7FF   // Accepts an exact ID (e.g., if one filter is 0x403--this mask will only match 0x403)
#define CAN_MASK_BASE_IDS       0x700   // Accepts a Base ID (e.g., if one filter is 0x400--this mask will accept 0x4xx, but not 0x5xx)
#define CAN_MASK_SUB_IDS        0x7F0   // Accepts sub-board IDs (e.g., if one filter is 0x410--this mask will accept 0x41x but not 0x40x)


enum {
    CAN_DATA_LENGTH     = 8,

    CAN_DEFAULT_FILTER  = 0x0000,
    CAN_DEFAULT_MASK    = CAN_MASK_EXACT_IDS
};

#endif