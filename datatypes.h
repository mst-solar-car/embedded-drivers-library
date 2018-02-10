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

#define __HIGH__  0x01
#define __LOW__   0x00

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
typedef uint8_t   io_pin;         /* Custom type to represent a pin */
typedef uint16_t  register_addr;  /* Represents a registry address */





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

  TRUE    = __TRUE__,
  True    = __TRUE__,
  true    = __TRUE__,
  Success = __TRUE__,
  Yes     = __TRUE__,
} bool;

/* Enum for pin direction */
typedef enum pin_mode_t {
  INPUT = __INPUT__,
  Input = __INPUT__,

  OUTPUT = __OUTPUT__,
  Output = __OUTPUT__
} pin_mode;

/* Enum for pin level */
typedef enum pin_level_t {
  LOW = __LOW__,
  Low = __LOW__,

  HIGH = __HIGH__,
  High = __HIGH__
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
#ifdef BIT0
#undef BIT0
#endif
  BIT0 = 0x0001,
#ifdef BIT1
#undef BIT1
#endif
  BIT1 = 0x0002,
#ifdef BIT2
#undef BIT2
#endif
  BIT2 = 0x0004,
#ifndef BIT3
#undef BIT3
#endif
  BIT3 = 0x0008,
#ifndef BIT4
#undef BIT4
#endif
  BIT4 = 0x0010,
#ifndef BIT5
#undef BIT5
#endif
  BIT5 = 0x0020,
#ifndef BIT6
#undef BIT6
#endif
  BIT6 = 0x0040,
#ifndef BIT7
#undef BIT7
#endif
  BIT7 = 0x0080,
#ifndef BIT8
#undef BIT8
#endif
  BIT8 = 0x0100,
#ifndef BIT9
#undef BIT9
#endif
  BIT9 = 0x0200,
#ifndef BITA
#undef BITA
#endif
  BITA = 0x0400,
#ifndef BITB
#undef BITB
#endif
  BITB = 0x0800,
#ifndef BITC
#undef BITC
#endif
  BITC = 0x1000,
#ifndef BITD
#undef BITD
#endif
  BITD = 0x2000,
#ifndef BITE
#undef BITE
#endif
  BITE = 0x4000,
#ifndef BITF
#undef BITF
#endif
  BITF = 0x8000,
};


/* Union */
typedef union group_64_t {
  float data_fp[2];           /* Holds floating point */
  unsigned char data_u8[8];   /* Holds 8 unsigned bits */
  char data_8[8];              /* Holds 8 signed bits */
  unsigned int data_u16[4];   /* Holds 16 unsigned bits */
  int data_16[4];             /* Holds 16 bits */
  unsigned long data_u32[2];  /* Holds 32 unsigned bits */
  long data_32[2];            /* Holds 32 bits */
} group_64;


/* Struct for a CAN Message */
typedef struct can_message_t {
  unsigned int  address;
  can_status  status;
  group_64      data;
} can_message;


/* Something for the internal workings of the microcontroller driver (i.e., DON'T WORRY ABOUT IT) */
typedef struct _pin_map_t {
  uint8_t port;
  uint8_t bit;
} pin_map_t;








#endif