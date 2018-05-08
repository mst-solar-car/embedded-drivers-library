/**
 * This file includes data types, aliases, and structs that are used throughout the
 * library and in user code
 *
 * Authors: Everyone?
 */
#ifndef __DATATYPES__
#define __DATATYPES__

/* Unassign the current NULL value because we will be assigning our own */
#ifdef NULL
#undef NULL
#endif


#define __NULL__    0x00

#define __TRUE__    1
#define __FALSE__   0

#define __HIGH__    0x01
#define __LOW__     0x00

#define __OUTPUT__  0xFF
#define __INPUT__   0x00


/* Assign types set by GCC if they are not defined for some reason */
#ifndef __INT8_TYPE__
#define __INT8_TYPE__ signed char
#endif
#ifndef __UINT8_TYPE__
#define __UINT8_TYPE__ unsigned char
#endif
#ifndef __INT16_TYPE__
#define __INT16_TYPE__ short int
#endif
#ifndef __UINT16_TYPE__
#define __UINT16_TYPE__ unsigned short int
#endif
#ifndef __INT32_TYPE__
#define __INT32_TYPE__ long int
#endif
#ifndef __UINT32_TYPE__
#define __UINT32_TYPE__ unsigned long int
#endif
#ifndef __INT64_TYPE__
#define __INT64_TYPE__ long long int
#endif
#ifndef __UINT64_TYPE__
#define __UINT64_TYPE__ unsigned long long int
#endif
#ifndef __VUINT8_TYPE__
#define __VUINT8_TYPE__ volatile unsigned char
#endif
#ifndef __VUINT16_TYPE__
#define __VUINT16_TYPE__ volatile unsigned short int
#endif

/* Now add type definitions that make typing code easier and prettier */
typedef __INT8_TYPE__     int8_t;
typedef __UINT8_TYPE__    uint8_t;
typedef __INT16_TYPE__    int16_t;
typedef __UINT16_TYPE__   uint16_t;
typedef __INT32_TYPE__    int32_t;
typedef __UINT32_TYPE__   uint32_t;
typedef __INT64_TYPE__    int64_t;
typedef __UINT64_TYPE__   uint64_t;

/* For memory stuff */
typedef __VUINT8_TYPE__   vuint8_t;
typedef __VUINT16_TYPE__  vuint16_t;

/* Aliases for types that are used often */
typedef uint8_t           io_pin;         /* Custom type to represent a pin */
typedef uint16_t          register_addr;  /* Represents a registry address */
typedef uint8_t           spi_bus;

typedef void(*voidFuncPtr)(void);


/**
 * Data Types
 */

/* Boolean values (plenty of names to help with readability) */
typedef enum bool_t {
  FALSE   = __FALSE__,
  False   = __FALSE__,
  false   = __FALSE__,
  Failure = __FALSE__,
  Busy    = __FALSE__,
  No      = __FALSE__,
  Disable = __FALSE__,

  TRUE    = __TRUE__,
  True    = __TRUE__,
  true    = __TRUE__,
  Success = __TRUE__,
  Yes     = __TRUE__,
  Enable  = __TRUE__,
} bool;

/* Enum for pin direction */
typedef enum pin_mode_t {
  INPUT   = __INPUT__,
  Input   = __INPUT__,

  OUTPUT  = __OUTPUT__,
  Output  = __OUTPUT__,
} pin_mode;

/* Enum for pin level */
typedef enum pin_level_t {
  LOW   = __LOW__,
  Low   = __LOW__,

  HIGH  = __HIGH__,
  High  = __HIGH__
} pin_level;


/* These are used to represent null values, there are different names to help with readability */
enum {
  NULL        = __NULL__,
  NOTHING     = __NULL__,
  EMPTY       = __NULL__,
  NO_PIN      = __NULL__,
  NO_REGISTER = __NULL__,
  NO_PORT     = __NULL__,
  NO_BIT      = __NULL__,
  NO_VECTOR   = __NULL__,
  NO_MESSAGE  = __NULL__,
  NO_LED      = __NULL__,
};

/* Status of a CAN Message */
typedef enum can_status_t {
  CAN_OK      = 0x0001,
  CAN_RTR     = 0xFFFC,
  CAN_WAKE    = 0xFFFD,
  CAN_MERROR  = 0xFFFE,
  CAN_ERROR   = 0xFFFF
} can_status;


/* Bits */
enum {
#undef BIT0
  BIT0 = 0x0001,
#undef BIT1
  BIT1 = 0x0002,
#undef BIT2
  BIT2 = 0x0004,
#undef BIT3
  BIT3 = 0x0008,
#undef BIT4
  BIT4 = 0x0010,
#undef BIT5
  BIT5 = 0x0020,
#undef BIT6
  BIT6 = 0x0040,
#undef BIT7
  BIT7 = 0x0080,
#undef BIT8
  BIT8 = 0x0100,
#undef BIT9
  BIT9 = 0x0200,
#undef BITA
  BITA = 0x0400,
#undef BITB
  BITB = 0x0800,
#undef BITC
  BITC = 0x1000,
#undef BITD
  BITD = 0x2000,
#undef BITE
  BITE = 0x4000,
#undef BITF
  BITF = 0x8000,

  MAX_BIT = BITF,
};


/**
 * This is a Union, it allows you store different datatypes in the same memory
 * location. We use this for CAN messages because we have different data (floats,
 * unsigned 8 bit, uinsigned 16 bits, etc...) that we send over CAN messages.
 *
 * This works, because sizeof(union_name) will evaluate to the size of the largest member.
 * In our case, that is the array of two int32_ts. 32x2 = 64, so this union will
 * always take up 64 bits of memory when used.
 */
typedef union group_64_t {
  float     data_fp[2];   /* Holds floating point */
  uint8_t   data_u8[8];   /* Holds 8 unsigned bits */
  int8_t    data_8[8];    /* Holds 8 signed bits */
  uint16_t  data_u16[4];  /* Holds 16 unsigned bits */
  int16_t   data_16[4];   /* Holds 16 bits */
  uint32_t  data_u32[2];  /* Holds 32 unsigned bits */
  int32_t   data_32[2];   /* Holds 32 bits */
} group_64;


/* Struct for a CAN Message */
typedef struct can_message_t {
  unsigned int  address;
  can_status    status;
  group_64      data;
} can_message;



#endif

/* Include internals */
#include "internals.h"
