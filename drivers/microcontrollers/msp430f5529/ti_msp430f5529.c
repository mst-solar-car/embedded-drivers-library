/**
 * This file contains all the arrays needed to map a value like P2_6 to the proper port and bit
 * for use in functions like setInput() or setOutput()
 *
 * Author: Michael Rouse
 */
#include "ti_msp430f5529.h"



// Converts a Port to a DIR register
const vuint16_t* dir_registers[] = {
  (vuint16_t*) NO_REGISTER,  // Place holder
  (vuint16_t*) P1DIR_REG,
  (vuint16_t*) P2DIR_REG,
  (vuint16_t*) P3DIR_REG,
  (vuint16_t*) P4DIR_REG,
  (vuint16_t*) P5DIR_REG,
  (vuint16_t*) P6DIR_REG,
  (vuint16_t*) P7DIR_REG,
  (vuint16_t*) P8DIR_REG,
  (vuint16_t*) PJDIR_REG
};


// Converts a Port to an OUT register
const vuint16_t* out_registers[] = {
  (vuint16_t*) NO_REGISTER, // Place holder
  (uint16_t*) P1OUT_REG,
  (uint16_t*) P2OUT_REG,
  (uint16_t*) P3OUT_REG,
  (uint16_t*) P4OUT_REG,
  (uint16_t*) P5OUT_REG,
  (uint16_t*) P6OUT_REG,
  (uint16_t*) P7OUT_REG,
  (uint16_t*) P8OUT_REG,
  (uint16_t*) PJOUT_REG
};

// Converts a Port to an IN register
const vuint16_t* in_registers[] = {
  (vuint16_t*) NO_REGISTER,  // Place holder
  (vuint16_t*) P1IN_REG,
  (vuint16_t*) P2IN_REG,
  (vuint16_t*) P3IN_REG,
  (vuint16_t*) P4IN_REG,
  (vuint16_t*) P5IN_REG,
  (vuint16_t*) P6IN_REG,
  (vuint16_t*) P7IN_REG,
  (vuint16_t*) P8IN_REG,
  (vuint16_t*) PJIN_REG
};


// Converts a Port to a SEL register
const vuint16_t* sel_registers[] = {
  (vuint16_t*) NO_REGISTER,  // Place holder
  (vuint16_t*) P1SEL_REG,
  (vuint16_t*) P2SEL_REG,
  (vuint16_t*) P3SEL_REG,
  (vuint16_t*) P4SEL_REG,
  (vuint16_t*) P5SEL_REG,
  (vuint16_t*) P6SEL_REG,
  (vuint16_t*) P7SEL_REG,
  (vuint16_t*) P8SEL_REG,
  (vuint16_t*) NO_REGISTER
};



// Map a pin to a port (e.g., Pin4 => P6.7 => PORT6)
const uint8_t port_map[] = {
  NO_PORT, // Place holder
  PORT6,
  PORT6,  // 2
  PORT6,
  PORT6,  // 4
  PORT7,
  PORT7,  // 6
  PORT7,
  PORT7,  // 8
  PORT5,
  PORT5,  // 10
  NO_PORT,
  PORT5,  // 12
  PORT5,
  NO_PORT, // 14
  PORT8,
  PORT8,  // 16
  PORT8,
  NO_PORT, // 18
  NO_PORT,
  NO_PORT, // 20
  PORT1,
  PORT1,  // 22
  PORT1,
  PORT1,  // 24
  PORT1,
  PORT1,  // 26
  PORT1,
  PORT1,  // 28
  PORT2,
  PORT2,  // 30
  PORT2,
  PORT2,  // 32
  PORT2,
  PORT2,  // 34
  PORT2,
  PORT2,  // 36
  PORT3,
  PORT3,  // 38
  PORT3,
  PORT3,  // 40
  PORT3,
  PORT3,  // 42
  PORT3,
  PORT3,  // 44
  PORT4,
  PORT4,  // 46
  PORT4,
  PORT4,  // 48
  NO_PORT,
  NO_PORT, // 50
  PORT4,
  PORT4,  // 52
  PORT4,
  PORT4,  // 54
  PORT5,
  PORT5,  // 56
  PORT7,
  PORT7,  // 58
  PORT7,
  PORT7,  // 60
  NO_PORT,
  NO_PORT, // 62 PU.0/DP
  NO_PORT,
  NO_PORT, // 64 PU.1/DM
  NO_PORT,
  NO_PORT, // 66 VUSB
  NO_PORT,
  NO_PORT, // 68 AVSS2
  PORT5,
  PORT5,  // 70
  NO_PORT,
  PORTJ,  // 72
  PORTJ,
  PORTJ,  // 74
  PORTJ,
  NO_PORT, // 76
  PORT6,
  PORT6,  // 78
  PORT6,
  PORT6   // 80
};


// Maps a pin to it's bit (e.g., Pin4 => P6.7 => BIT7)
const uint8_t bit_map[] = {
  NO_PIN,   // Place holder
  BIT4,
  BIT5,
  BIT6,
  BIT7,
  BIT0,
  BIT1,
  BIT2,
  BIT3,
  BIT0,
  BIT1,
  NO_BIT,
  BIT4,
  BIT5,
  NO_BIT,
  BIT0,
  BIT1,
  BIT2,
  NO_BIT,
  NO_BIT,
  NO_BIT,
  BIT0,
  BIT1,
  BIT2,
  BIT3,
  BIT4,
  BIT5,
  BIT6,
  BIT7,
  BIT0,
  BIT1,
  BIT2,
  BIT3,
  BIT4,
  BIT5,
  BIT6,
  BIT7,
  BIT0,
  BIT1,
  BIT2,
  BIT3,
  BIT4,
  BIT5,
  BIT6,
  BIT7,
  BIT0,
  BIT1,
  BIT2,
  BIT3,
  NO_BIT,
  NO_BIT,
  BIT4,
  BIT5,
  BIT6,
  BIT7,
  BIT6,
  BIT7,
  BIT4,
  BIT5,
  BIT6,
  BIT7,
  NO_BIT,
  NO_BIT,
  NO_BIT,
  NO_BIT,
  NO_BIT,
  NO_BIT,
  NO_BIT,
  NO_BIT,
  BIT2,
  BIT3,
  NO_BIT,
  BIT0,
  BIT1,
  BIT2,
  BIT3,
  NO_BIT,
  BIT0,
  BIT1,
  BIT2,
  BIT3
};





/**
 * Setup function for the microcontroller 
 */
void microcontroller_setup(void) 
{ 
  // Configure each pin as OUTPUT and set all bits LOW initially
  setRegister(getDirReg(PORT1), OUTPUT);  setRegister(getOutReg(PORT1), LOW);
  setRegister(getDirReg(PORT2), OUTPUT);  setRegister(getOutReg(PORT2), LOW);
  setRegister(getDirReg(PORT3), OUTPUT);  setRegister(getOutReg(PORT3), LOW);
  setRegister(getDirReg(PORT4), OUTPUT);  setRegister(getOutReg(PORT4), LOW);
  setRegister(getDirReg(PORT5), OUTPUT);  setRegister(getOutReg(PORT5), LOW);
  setRegister(getDirReg(PORT6), OUTPUT);  setRegister(getOutReg(PORT6), LOW);
  setRegister(getDirReg(PORT7), OUTPUT);  setRegister(getOutReg(PORT7), LOW);
  setRegister(getDirReg(PORT8), OUTPUT);  setRegister(getOutReg(PORT8), LOW);


  // Initialize the clock 

}

