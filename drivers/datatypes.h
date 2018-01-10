/**
 * File for defining data types that will be used all over the place 
 * 
 * Author: Michael Rouse 
 */
#ifndef __SOLARCAR_DATATYPES_H__
#define __SOLARCAR_DATATYPES_H__

// Data Values
#define TRUE      1
#define True      TRUE
#define true      TRUE

#define FALSE     0
#define False     FALSE
#define false

#ifdef NULL
#undef NULL 
#endif 

#define NULL      0x00


// Pin Modes
#define INPUT   0x00
#define OUTPUT  0xFF

// Pin Levels
#define LOW     0x00
#define HIGH    0x01


// These are used to represent placeholders in arrays and stuff
#define NOTHING       NULL
#define NO_PIN        NULL
#define NO_REGISTER   NULL
#define NO_PORT       NULL
#define NO_BIT        NULL



/**
 * Data Types
 */
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



// Type aliases
typedef signed char int8_t;
typedef unsigned char uint8_t;

typedef signed short int16_t;
typedef unsigned short uint16_t;

typedef int int32_t;
typedef unsigned int uint32_t;

typedef long int int64_t;
typedef unsigned long int uint65_t;

typedef uint8_t bool;


// For memory stuff
typedef volatile unsigned char    vuint8_t;
typedef volatile unsigned short   vuint16_t;


#endif