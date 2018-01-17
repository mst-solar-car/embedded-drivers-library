/**
 * File for defining data types that will be used all over the place
 *
 * Author: Michael Rouse
 */
#include "microcontrollers/spec_importer.h"

#ifndef __DATATYPES_H__
#define __DATATYPES_H__

// Unassign the current NULL value because we will be assigning our own
#ifdef NULL
#undef NULL
#endif

#define __NULL__    0x00

#define __TRUE__    1
#define __FALSE__   0

#define __HIGH_PIN__  0x01
#define __LOW_PIN__   0x00

#define __OUTPUT_PIN__  0xFF
#define __INPUT_PIN__   0x00



// Assign types set by GCC if they are not defined for some reason
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


// Now add type definitions that make typing code easier and prettier
typedef __INT8_TYPE__     int8_t;
typedef __UINT8_TYPE__    uint8_t;
typedef __INT16_TYPE__    int16_t;
typedef __UINT16_TYPE__   uint16_t;
typedef __INT32_TYPE__    int32_t;
typedef __UINT32_TYPE__   uint32_t;
typedef __INT64_TYPE__    int64_t;
typedef __UINT64_TYPE__   uint64_t;

// For memory stuff
typedef __VUINT8_TYPE__   vuint8_t;
typedef __VUINT16_TYPE__  vuint16_t;

// Aliases for types that are used often
typedef uint8_t io_pin;     // Custom type to represent a pin

typedef void(*voidFuncPtr)(void);



/**
 * Data Types
 */
// Boolean values (plenty of names to help with readability)
typedef enum bool_t {
  FALSE   = __FALSE__,
  False   = __FALSE__,
  Failure = __FALSE__,
  Busy    = __FALSE__,

  TRUE    = __TRUE__,
  True    = __TRUE__,
  Success = __TRUE__
} bool;

// Enum for pin direction
typedef enum pin_mode_t {
  INPUT = __INPUT_PIN__,
  Input = __INPUT_PIN__,

  OUTPUT = __OUTPUT_PIN__,
  Output = __OUTPUT_PIN__
} pin_mode;

// Enum for pin level
typedef enum pin_level_t {
  LOW = __LOW_PIN__,
  Low = __LOW_PIN__,

  HIGH = __HIGH_PIN__,
  High = __HIGH_PIN__
} pin_level;

// Enum for SPI Bus identifiers
typedef enum spi_bus_t {
#ifndef MC_NO_SPI
  SPI_BUS_1 = 1,
#if MC_NUM_SPI_BUSSES > 1
  SPI_BUS_2,
#endif
#if MC_NUM_SPI_BUSSES > 2
  SPI_BUS_3,
#endif
#if MC_NUM_SPI_BUSSES > 3
  SPI_BUS_4,
#endif
#if MC_NUM_SPI_BUSSES > 4
  SPI_BUS_5,
#endif
#if MC_NUM_SPI_BUSSES > 5
  SPI_BUS_6,
#endif
#if MC_NUM_SPI_BUSSES > 6
  #error "PLEASE ADD MORE SPI BUSSES TO datatypes.h"
#endif
#endif
} spi_bus;


// These are used to represent null values, there are different names to help with readability
enum {
  NULL        = __NULL__,
  NOTHING     = __NULL__,
  EMPTY       = __NULL__,
  NO_PIN      = __NULL__,
  NO_REGISTER = __NULL__,
  NO_PORT     = __NULL__,
  NO_BIT      = __NULL__,
  NO_VECTOR   = __NULL__
};



// Union
typedef union group_64_t {
  float data_fp[2];           // Holds floating point
  unsigned char data_u8[8];   // Holds 8 unsigned bits
  char data_8[8];              // Holds 8 signed bits
  unsigned int data_u16[4];   // Holds 16 unsigned bits
  int data_16[4];             // Holds 16 bits
  unsigned long data_u32[2];  // Holds 32 unsigned bits
  long data_32[2];            // Holds 32 bits
} group_64;


// Struct for a CAN Message
typedef struct can_message_t {
  unsigned int  address;
  unsigned int  status;
  group_64      data;
} can_message;



#endif
