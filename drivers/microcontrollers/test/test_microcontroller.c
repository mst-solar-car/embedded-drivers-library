/**
 * Implementation of the Test Microcontroller drivers. 
 * These are used for unit testing. 
 *
 * Author: Michael Rouse
 */

#ifdef UNIT_TEST
// FIRST thing first: include the header file for your driver implementation
#include "test_microcontroller.h"


// The dir_registers array is declared in microcontroller.h 
// It holds pointers to the memory locations of registers used to set the direction
// (INPUT or OUTPUT) of PORTS.
const vuint16_t* dir_registers[] = {
  (vuint16_t*)  NO_REGISTER, // Placeholder, since there is no PORT0 code could get confusing 
  (vuint16_t*)  NULL // Pointer to memory address 0x00, this will change 
};


// The out_registers array is declared in microcontroller.h
// It holds pointers to memory locations of registers used to set the output 
// state of pins (HIGH or LOW) 
const vuint16_t* out_registers[] = { 
  (vuint16_t*)  NO_REGISTER, // Placeholder, since there is no PORT0 code could get confusing 
  (vuint16_t*)  NULL  // Again, this will change to the memory location of the variables we are using to simulate registers
};


// The in_registers array is declared in microcontroller.h 
// It holds pointers to registers used to get the state of a pin (for INPUT) 
// (HIGH or LOW) 
const vuint16_t* in_registers[] = { 
  (vuint16_t*)  NO_REGISTER, // Again, a placeholder since there is no PORT0
  (vuint16_t*)  NULL  // Will change 
};


// The sel_registers array is declared in microcontroller.h 
// It holds pointers to registers used for selection or something 
const vuint16_t* sel_registers[] = { 
  (vuint16_t*)  NO_REGISTER, // Still a placeholder for the same reason 
  (vuint16_t*)  NULL  // Will be changed just like all the others
};


// port_map array is also declared in microcontroller.h 
// It is used to map a pin to a port. So if PINx of your microcontroller
// connects to PORTy then in the xth position in this array should be the 
// index of PORTy in the previous arrays. 
const uint8_t port_map[] = {
  (uint8_t) NO_PORT, // Also a placeholder 
  PORT1, 
  PORT1, 
  PORT1, 
  PORT1,  // All pins on our "microcontroller" connect to PORT1
  PORT1, 
  PORT1, 
  PORT1, 
  PORT1
};


// bit_map array is declared in microcontroller.h 
// This array is very similar to port_map. Except instead of mapping 
// to the PORT, it maps a pin to the BIT that pin connects to in the PORT. 
const uint8_t bit_map[] = {
  (uint8_t) NO_BIT, // Can you guess what this is? Is it a placeholder? Who knows!? 
  BIT0, 
  BIT1, 
  BIT2, 
  BIT3, 
  BIT4, 
  BIT5, 
  BIT6, 
  BIT7
};


// Allocate memory for "registers"
// These are used for the purpose of unit testing
uint16_t*  port1_dir_reg; 
uint16_t*  port1_out_reg; 
uint16_t*  port1_in_reg; 
uint16_t*  port1_sel_reg; 



#include <stdlib.h> // This should NOT be in your implementation file, this is needed for malloc


// The microcontroller_setup() function is declared in microcontroller.h (shocker) 
// It is MANDATORY. 
// This function is responsible for initializing your microcontroller, 
// this could include: configuring clock, disabling watchdogs, setting default
//                      pin states, etc. 
// It should not require any (or very very very little [if ever]) user configuration 
void microcontroller_setup(void) 
{ 
  // In a real microcontroller you would use this function to set default pin states, 
  // like making all of them output, and making sure the states are all LOW. 
  // But since this is not a real microcontroller, and it is used for unit tests
  // We have to allocate memory for the pointers we are using as registers
  // we also initialize all that memory to be all 0s
  port1_dir_reg = malloc(sizeof(uint16_t)); 
  setRegister(port1_dir_reg, LOW); 

  port1_out_reg = malloc(sizeof(uint16_t)); 
  setRegister(port1_out_reg, LOW);

  port1_in_reg = malloc(sizeof(uint16_t)); 
  setRegister(port1_in_reg, LOW);

  port1_sel_reg = malloc(sizeof(uint16_t)); 
  setRegister(port1_sel_reg, LOW);

  
  // Now, we update the arrays created outside of this function and point them 
  // to the pointers 
  dir_registers[1] = (vuint16_t*) port1_dir_reg;
  out_registers[1] = (vuint16_t*) port1_out_reg; 
  in_registers[1]  = (vuint16_t*) port1_in_reg; 
  sel_registers[1] = (vuint16_t*) port1_sel_reg;


  // Here, after initializing ports is where you would do stuff 
  // like configure clock and other basic stuff. 
}


#endif