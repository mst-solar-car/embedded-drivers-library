/**
 * File for defining data types that will be used all over the place
 *
 * Author: Michael Rouse
 */
#ifndef __DATATYPES_H__
#define __DATATYPES_H__

// Unassign the current NULL value because we will be assigning our own
#ifdef NULL
#undef NULL
#endif

#define __NULL__    0x00
#define __FALSE__   0
#define __TRUE__    1


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


typedef uint8_t io_pin;   // Custom type to represent a pin
typedef uint8_t spi_bus;  // SPI bus ID



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
  INPUT = 0x00,
  Input = 0x00,

  Interrupt = 0x0F,

  OUTPUT = 0xFF,
  Output = 0xFF
} pin_mode;

// Enum for pin level
typedef enum pin_level_t {
  LOW = 0x00,
  Low = 0x00,

  HIGH = 0x01,
  High = 0x01
} pin_level;

// These are used to represent null values, there are different names to help with readability
enum {
  NULL        = __NULL__,
  NOTHING     = __NULL__,
  EMPTY       = __NULL__,
  NO_PIN      = __NULL__,
  NO_REGISTER = __NULL__,
  NO_PORT     = __NULL__,
  NO_BIT      = __NULL__
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


// Struct for a SPI Bus configuration
typedef struct spi_bus_config_t {
  uint8_t mosi; // Pin used for MOSI
  uint8_t miso; // Pin used for MISO
  uint8_t sck;  // Pin used for SCK
} spi_bus_config;




#endif