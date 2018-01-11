/**
 * This "microcontroller" is only used when unit tests are running.
 * 
 * It can be a great example of how to go about creating your own 
 * microcontroller driver implementation, if ever needed. 
 * This and the test_microcontroller.c file are going to be very documented.
 * 
 * 
 * This "microcontroller" has the following schematic: 
 *           _______
 *    P1.0 -|1     5|- P1.4
 *    P1.1 -|2     6|- P1.5
 *    P1.2 -|3     7|- P1.6
 *    P1.3 -|4_____8|- P1.7
 * 
 * It has 8 pins, all are GPIO pins which connect to the PORT1 register. 
 *
 * Author: Michael Rouse
 */

// Your microcontroller header MUST define __MICROCONTROLLER__, nothing else
#ifdef UNIT_TEST
#ifndef __MICROCONTROLLER__
#define __MICROCONTROLLER__

// Import the microcontroller.h file, this will give you access to datatypes.h, 
// it will also declare functions and variables needed
#include "../microcontroller.h" 


// As of this time, this "microcontroller" does not support 
// interrupts or a watchdog timer
#define NO_INTERRUPTS 
#define NO_WATCHDOG 

// This "microcontroller" has a 5 Hz clock! (TOO FAST 4 ME)
#define MICROCONTROLLER_CLOCK   5


// As stated in the giant comment block at the beginning of this file, 
// this microcontroller only has one PORT, PORT1
//
// The values of these PORT definitions should correspond to an index in the arrays
#define PORT1   1


// Assignment for the 8 pins, these should map to tan index in the port_map array 
// These let you do things like use "PINx" in your code
#define PIN1    1
#define PIN2    2
#define PIN3    3
#define PIN4    4
#define PIN5    5
#define PIN6    6
#define PIN7    7
#define PIN8    8


// Aliases for ports, these just map directly to the pin directives, they also juts make writing code easier
#define P1_0    PIN1 
#define P1_1    PIN2
#define P1_2    PIN3
#define P1_3    PIN4 
#define P1_4    PIN5 
#define P1_5    PIN6 
#define P1_6    PIN7
#define P1_7    PIN8


// Now, these are something that you should NOT have in a regular microcontroller 
// driver implementation file. These are here for the sole purpose of UNIT TESTING.
// Since unit testing on hardware can be difficult, these variables are here 
// to simulate what would be actual registers on the microcontroller. 
// We can use these variables as registers and be able to confirm that the values 
// in them have changed.
extern uint16_t*  port1_dir_reg; 
extern uint16_t*  port1_out_reg; 
extern uint16_t*  port1_in_reg; 
extern uint16_t*  port1_sel_reg; 


#endif
#endif