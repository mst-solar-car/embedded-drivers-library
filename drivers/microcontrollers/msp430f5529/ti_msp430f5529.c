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
  // Disable watchdog 
  #ifndef NO_WATCHDOG
  watchdog_disable();
  #endif

  // Configure each pin as OUTPUT and set all bits LOW initially
  setRegister(getDirReg(PORT1), OUTPUT);  setRegister(getOutReg(PORT1), LOW);
  setRegister(getDirReg(PORT2), OUTPUT);  setRegister(getOutReg(PORT2), LOW);
  setRegister(getDirReg(PORT3), OUTPUT);  setRegister(getOutReg(PORT3), LOW);
  setRegister(getDirReg(PORT4), OUTPUT);  setRegister(getOutReg(PORT4), LOW);
  setRegister(getDirReg(PORT5), OUTPUT);  setRegister(getOutReg(PORT5), LOW);
  setRegister(getDirReg(PORT6), OUTPUT);  setRegister(getOutReg(PORT6), LOW);
  setRegister(getDirReg(PORT7), OUTPUT);  setRegister(getOutReg(PORT7), LOW);
  setRegister(getDirReg(PORT8), OUTPUT);  setRegister(getOutReg(PORT8), LOW);

  // Enable interrupts (by default)
  #ifndef NO_INTERRUPTS 
  interrupts_enable()
  #endif 


  // Initialize the clock (by Jesse Cureton)
  UCSCTL3 &= ~(0x0070);   // Select XT1CLK (our 32.768 kHz crystal) as FLL reference
  UCSCTL4 &= ~(0x0070);   // Select XT1CLK as ACLK 

  uint16_t ratio, dco_div_bits;
  uint8_t mode = 0; 

  uint16_t sysfreq = MICROCONTROLLER_CLOCK_HZ / 1000; // Get clock in kHz
  ratio = MICROCONTROLLER_CLOCK_HZ / 32768; // Ratio of clock and crystal frequency
  dco_div_bits = FLLD__2;

  if (sysfreq > 1600) { 
    ratio >>= 1; 
    mode = 1;       // If sysfreq > 16 MHz then use DC0CLK not DC0CLKDIV
  }
  else sysfreq <<= 1;

  while (ratio > 512) { 
    // Step up to a next div level 
    dco_div_bits += FLLD0; 
    ratio >>= 1;
  }

  __bis_SR_register(SCG0);  // Disable FLL while changing clocks 

  UCSCTL0 = 0x0000;                       //Set the DCO to the lowest tap setting

  UCSCTL2 &= ~(0x3FF);                    //Clear the 8 LSBs in the register to clear the FLLN bits
  UCSCTL2 = dco_div_bits | (ratio - 1);   //Datasheet voodoo

  //sysfreq is in kHz
  if (sysfreq <= 630)                     //Set the proper DCORSEL value
    UCSCTL1= DCORSEL_0;
  else if (sysfreq <  1250)
    UCSCTL1= DCORSEL_1;
  else if (sysfreq <  2500)
    UCSCTL1= DCORSEL_2;
  else if (sysfreq <  5000)
    UCSCTL1= DCORSEL_3;
  else if (sysfreq <  10000)
    UCSCTL1= DCORSEL_4;
  else if (sysfreq <  20000)
    UCSCTL1= DCORSEL_5;
  else if (sysfreq <  40000)
    UCSCTL1= DCORSEL_6;
  else
    UCSCTL1= DCORSEL_7;

  __bic_SR_register(SCG0);                //Re-enable the FLL

  /* In theory this should be required, but it was hanging because these were apparently never being cleared?
    * I dunno. It works without them. If something breaks with the clocks and hanging at init, it's probably here
    *
    * while(SFRIFG1 & OFIFG) {
      UCSCTL7 &= ~(DCOFFG+XT1LFOFFG+XT2OFFG);
      SFRIFG1 &= ~OFIFG;
  }*/

  if(mode == 1) {                         //select DCOCLK
    UCSCTL4 &= ~(0x0077);
    UCSCTL4 |= 0x0033;
  } else {                                //Select DCOCLKDIV
    UCSCTL4 &= ~(0x0077);
    UCSCTL4 |= 0x0044;
  }

  // Worst-case settling time for the DCO when the DCO range bits have been
  // changed is n x 32 x 32 x f_MCLK / f_FLL_reference. See UCS chapter in 5xx
  // UG for optimization.
  // 32 x 32 x 20 MHz / 32,768 Hz = 625000 MCLK cycles for DCO to settle
  __delay_cycles(625000);
}

