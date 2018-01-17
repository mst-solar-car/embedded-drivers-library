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


// Converts a Port to IES registers
const vuint16_t* ies_registers[] = {
  (vuint16_t*) NO_REGISTER, // Place holder
  (vuint16_t*) P1IES_REG,
  (vuint16_t*) P2IES_REG,
  (vuint16_t*) NO_REGISTER,
  (vuint16_t*) NO_REGISTER,
  (vuint16_t*) NO_REGISTER,
  (vuint16_t*) NO_REGISTER,
  (vuint16_t*) NO_REGISTER,
  (vuint16_t*) NO_REGISTER,
  (vuint16_t*) NO_REGISTER
};


// Converts a Port to IE register
const vuint16_t* ie_registers[] = {
  (vuint16_t*) NO_REGISTER, // Place Holder
  (vuint16_t*) P1IE_REG,
  (vuint16_t*) P2IE_REG,
  (vuint16_t*) NO_REGISTER,
  (vuint16_t*) NO_REGISTER,
  (vuint16_t*) NO_REGISTER,
  (vuint16_t*) NO_REGISTER,
  (vuint16_t*) NO_REGISTER,
  (vuint16_t*) NO_REGISTER,
  (vuint16_t*) NO_REGISTER
};


// Converts a Port to IFG register
const vuint16_t* ifg_registers[] = {
  (vuint16_t*) NO_REGISTER, // Place holder
  (vuint16_t*) P1IFG_REG,
  (vuint16_t*) P2IFG_REG,
  (vuint16_t*) NO_REGISTER,
  (vuint16_t*) NO_REGISTER,
  (vuint16_t*) NO_REGISTER,
  (vuint16_t*) NO_REGISTER,
  (vuint16_t*) NO_REGISTER,
  (vuint16_t*) NO_REGISTER,
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
  watchdog_disable();

  // Configure each pin as OUTPUT and set all bits LOW initially
  setRegister(dirReg(PORT1), OUTPUT);  setRegister(outReg(PORT1), LOW);
  setRegister(dirReg(PORT2), OUTPUT);  setRegister(outReg(PORT2), LOW);
  setRegister(dirReg(PORT3), OUTPUT);  setRegister(outReg(PORT3), LOW);
  setRegister(dirReg(PORT4), OUTPUT);  setRegister(outReg(PORT4), LOW);
  setRegister(dirReg(PORT5), OUTPUT);  setRegister(outReg(PORT5), LOW);
  setRegister(dirReg(PORT6), OUTPUT);  setRegister(outReg(PORT6), LOW);
  setRegister(dirReg(PORT7), OUTPUT);  setRegister(outReg(PORT7), LOW);
  setRegister(dirReg(PORT8), OUTPUT);  setRegister(outReg(PORT8), LOW);

  // Enable interrupts
  interrupts_enable();


  // Initialize the clock (by Jesse Cureton)
  UCSCTL3 &= ~(0x0070);   // Select XT1CLK (our 32.768 kHz crystal) as FLL reference
  UCSCTL4 &= ~(0x0070);   // Select XT1CLK as ACLK

  uint16_t ratio, dco_div_bits;
  uint8_t mode = 0;

  uint16_t sysfreq = MC_CLOCK_HZ / 1000; // Get clock in kHz
  ratio = MC_CLOCK_HZ / 32768; // Ratio of clock and crystal frequency
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




/**
 * Configure a SPI Bus
 */
void microcontroller_spi_setup(spi_bus bus)
{
  switch (bus) {
    case SPI_BUS_1:
      // UCA0
      break;

    case SPI_BUS_2:
      // UCA1
      break;

    case SPI_BUS_3:
      // UCB0
      break;

    case SPI_BUS_4:
      // UCB1
      UCB1CTL1  = UCSWRST;    //Hold the device in a reset state while we configure
      UCB1CTL0  = 0x69;       //SPI mode 11, MSB first, 8 bit data, 3pin master synchronous mode
      UCB1CTL1 |= UCSSEL_3;       //SPI clock (BRCLK) source = SMCLK
      UCB1BR1   = 0x00;       //Set the high bit of the baud rate generator
      UCB1BR0   = 0x14;       //Set the low bit of the baud rate generator (SMCLK / 20 == 1MHz SPI)
      //UCB0IE   |= 0x04;     //Enable interrupts
      UCB1CTL1 &= ~UCSWRST;   //Release the bus from reset state
      break;
  }
}


/**
 * Send Data over a SPI bus
 */
uint8_t microcontroller_spi_transmit(spi_bus bus, uint8_t data)
{
  switch (bus) {
    case SPI_BUS_1:
      // UCA0
      while ((UCA0STAT & BIT1) != 0);
      UCA0TXBUF = data;
      while ((UCA0STAT & BIT0) != 0);
      return UCA0RXBUF;

    case SPI_BUS_2:
      // UCA1
      while ((UCA1STAT & BIT1) != 0);
      UCA1TXBUF = data;
      while ((UCA1STAT & BIT0) != 0);
      return UCA1RXBUF;

    case SPI_BUS_3:
      // UCB0
      while ((UCB0STAT & BIT1) != 0);
      UCB0TXBUF = data;
      while ((UCB0STAT & BIT0) != 0);
      return UCB0RXBUF;

    case SPI_BUS_4:
      // UCB1
      while ((UCB1STAT & BIT1) != 0);
      UCB1TXBUF = data;
      while ((UCB1STAT & BIT0) != 0);
      return UCB1RXBUF;
  }

  return 0;
}


// Register PIN Interrupts
REGISTER_PIN_INTERRUPT(PORT1_VECTOR, PORT1);
REGISTER_PIN_INTERRUPT(PORT2_VECTOR, PORT2);

