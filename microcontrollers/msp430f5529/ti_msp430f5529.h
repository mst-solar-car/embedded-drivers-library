/**
 * This file contains all the arrays needed to map a value like P2_6 to the proper port and bit
 * for use in functions like setInput() or setOutput()
 *
 * Author: Michael Rouse
 */
#ifndef MICROCONTROLLER
#define MICROCONTROLLER

#ifndef UNIT_TEST
#include <msp430f5529.h>
#else
#define _no_operation() // Nothing :)
#endif

#include "ti_msp430f5529.spec"
#include "../microcontroller.h"


/**
 * Modules
 */
#define no_operation()    _no_operation() // Does nothing in code, can be used as a breakpoint (won't be removed by optimization)

// Watchdog
#define watchdog_disable()      WDTCTL = WDTPW + WDTHOLD
#define watchdog_enable()       WDTCTL = WDT_ARST_1000    // Reset every 1 second (1000ms)
#define watchdog_pet()          WDTCTL = WDTPW + WDTCNTCL  // Clear Watchdog timer (prevents reset)


// Interrupts
#define interrupts_enable()     __bis_SR_register(GIE) //_enable_interrupts()
#define interrupts_disable()    __bic_SR_register(GIE) //_disable_interrupts()


// Port names mapped to an integer for use in an array
enum {
  PORT1 = 1,
  PORT2,
  PORT3,
  PORT4,
  PORT5,
  PORT6,
  PORT7,
  PORT8,
  PORTJ
};


// Enums for each pin on the microcontroller
enum {
  PIN1 = 1,
  PIN2,
  PIN3,
  PIN4,
  PIN5,
  PIN6,
  PIN7,
  PIN8,
  PIN9,
  PIN10,
  PIN11,
  PIN12,
  PIN13,
  PIN14,
  PIN15,
  PIN16,
  PIN17,
  PIN18,
  PIN19,
  PIN20,
  PIN21,
  PIN22,
  PIN23,
  PIN24,
  PIN25,
  PIN26,
  PIN27,
  PIN28,
  PIN29,
  PIN30,
  PIN31,
  PIN32,
  PIN33,
  PIN34,
  PIN35,
  PIN36,
  PIN37,
  PIN38,
  PIN39,
  PIN40,
  PIN41,
  PIN42,
  PIN43,
  PIN44,
  PIN45,
  PIN46,
  PIN47,
  PIN48,
  PIN49,
  PIN50,
  PIN51,
  PIN52,
  PIN53,
  PIN54,
  PIN55,
  PIN56,
  PIN57,
  PIN58,
  PIN59,
  PIN60,
  PIN61,
  PIN62,
  PIN63,
  PIN64,
  PIN65,
  PIN66,
  PIN67,
  PIN68,
  PIN69,
  PIN70,
  PIN71,
  PIN72,
  PIN73,
  PIN74,
  PIN75,
  PIN76,
  PIN77,
  PIN78,
  PIN79,
  PIN80
};


// Port 1
enum {
  P1_0 = PIN21,
  P1_1 = PIN22,
  P1_2 = PIN23,
  P1_3 = PIN24,
  P1_4 = PIN25,
  P1_5 = PIN26,
  P1_6 = PIN27,
  P1_7 = PIN28
};

// Port 2
enum {
  P2_0 = PIN29,
  P2_1 = PIN30,
  P2_2 = PIN31,
  P2_3 = PIN32,
  P2_4 = PIN33,
  P2_5 = PIN34,
  P2_6 = PIN35,
  P2_7 = PIN36
};

// Port 3
enum {
  P3_0 = PIN37,
  P3_1 = PIN38,
  P3_2 = PIN39,
  P3_3 = PIN40,
  P3_4 = PIN41,
  P3_5 = PIN42,
  P3_6 = PIN43,
  P3_7 = PIN44
};

// Port 4
enum {
  P4_0 = PIN45,
  P4_1 = PIN46,
  P4_2 = PIN47,
  P4_3 = PIN48,
  P4_4 = PIN51,
  P4_5 = PIN52,
  P4_6 = PIN53,
  P4_7 = PIN54
};

// Port 5
enum {
  P5_0 = PIN9,
  P5_1 = PIN10,
  P5_2 = PIN69,
  P5_3 = PIN70,
  P5_4 = PIN12,
  P5_5 = PIN13,
  P5_6 = PIN55,
  P5_7 = PIN56
};

// Port 6
enum {
  P6_0 = PIN77,
  P6_1 = PIN78,
  P6_2 = PIN79,
  P6_3 = PIN80,
  P6_4 = PIN1,
  P6_5 = PIN2,
  P6_6 = PIN3,
  P6_7 = PIN4
};

// Port 7
enum {
  P7_0 = PIN5,
  P7_1 = PIN6,
  P7_2 = PIN7,
  P7_3 = PIN8,
  P7_4 = PIN57,
  P7_5 = PIN58,
  P7_6 = PIN59,
  P7_7 = PIN60
};

// Port 8
enum {
  P8_0 = PIN15,
  P8_1 = PIN16,
  P8_2 = PIN17
};

// Port J
enum {
  PJ_0 = PIN72,
  PJ_1 = PIN73,
  PJ_2 = PIN74,
  PJ_3 = PIN75
};



// Other names for pins
enum {
  XIN = PIN12,
  XOUT = PIN13,
  XT2IN = PIN69,
  XT2OUT = PIN70,
  TA0CLK = PIN21,
  TA1CLK = PIN27,
  TA2CLK = PIN32,
  TB0CLK = PIN60,
  RTCCLK = PIN35,
  UCB0STE = PIN36,
  UCB0SIMO = PIN37,
  UCB0SOMI = PIN38,
  UCB0SDA = PIN37,
  UCB0SCL = PIN38,
  UCB0CLK = PIN39,
  UCA0CLK = PIN36,
  UCA0STE = PIN39,
  UCA0TXD = PIN40,
  UCA0SIMO = PIN40,
  UCA0RXD = PIN41,
  UCA0SOMI = PIN41,
  TB0OUTH = PIN44,
  SVMOUT = PIN44,
  TCK = PIN75,
  TMS = PIN74,
  TCLK = PIN73,
  TDI = PIN73,
  TDO = PIN72,
  TEST = PIN71,
  SBWTCK = PIN71
};



/**
 * Register addresses for MSP430F5529
 * These can be found using the datasheet or the msp430f5529_symbols.ld linker script.
 *
 * These are needed because if you try to place the value P1OUT in the arrays in the .c file you'll
 * get an error saying it's not constant. That's because P1OUT is actually a variable set using the
 * linker script. These are the values set by the linker script. Dumb. But it's needed.
 */
// Registers for PORT1
enum {
  P1IN_REG  = 0x0200,
  P1OUT_REG = 0x0202,
  P1DIR_REG = 0x0204,
  P1SEL_REG = 0x020A,
  P1IES_REG = 0x0218,
  P1IE_REG  = 0x021A,
  P1IFG_REG = 0x021C
};

// Registers for PORT2
enum {
  P2IN_REG  = 0x0201,
  P2OUT_REG = 0x0203,
  P2DIR_REG = 0x0205,
  P2SEL_REG = 0x020B,
  P2IES_REG = 0x0219,
  P2IE_REG  = 0x021B,
  P2IFG_REG = 0x021D
};

// Registers for PORT3
enum {
  P3IN_REG  = 0x0220,
  P3OUT_REG = 0x0222,
  P3DIR_REG = 0x0224,
  P3SEL_REG = 0x022A
};

// Registers for PORT4
enum {
  P4IN_REG  = 0x0221,
  P4OUT_REG = 0x0223,
  P4DIR_REG = 0x0225,
  P4SEL_REG = 0x022B
};

// Registers for PORT5
enum {
  P5IN_REG  = 0x0240,
  P5OUT_REG = 0x0242,
  P5DIR_REG = 0x0244,
  P5SEL_REG = 0x024A
};

// Registers for PORT6
enum {
  P6IN_REG  = 0x0241,
  P6OUT_REG = 0x0243,
  P6DIR_REG = 0x0245,
  P6SEL_REG = 0x025B
};

// Registers for PORT7
enum {
  P7IN_REG  = 0x0260,
  P7OUT_REG = 0x0262,
  P7DIR_REG = 0x0264,
  P7SEL_REG = 0x026A
};

// Registers for PORT8
enum {
  P8IN_REG  = 0x0261,
  P8OUT_REG = 0x0262,
  P8DIR_REG = 0x0265,
  P8SEL_REG = 0x026B
};

// Registers for PORTJ
enum {
  PJIN_REG = 0x0320,
  PJOUT_REG = 0x0322,
  PJDIR_REG = 0x0324
};



#ifdef UNIT_TEST
// Fake registers
extern reg(p1_dir); extern reg(p2_dir); extern reg(p3_dir); extern reg(p4_dir); extern reg(p5_dir); extern reg(p6_dir);
extern reg(p7_dir); extern reg(p8_dir); extern reg(pj_dir);

extern reg(p1_out); extern reg(p2_out); extern reg(p3_out); extern reg(p4_out); extern reg(p5_out); extern reg(p6_out);
extern reg(p7_out); extern reg(p8_out); extern reg(pj_out);

extern reg(p1_in); extern reg(p2_in); extern reg(p3_in); extern reg(p4_in); extern reg(p5_in); extern reg(p6_in);
extern reg(p7_in); extern reg(p8_in); extern reg(pj_in);

extern reg(p1_sel); extern reg(p2_sel); extern reg(p3_sel); extern reg(p4_sel); extern reg(p5_sel); extern reg(p6_sel);
extern reg(p7_sel); extern reg(p8_sel);

extern reg(p1_ies); extern reg(p2_ies);
extern reg(p1_ie);  extern reg(p2_ie);
extern reg(p1_ifg); extern reg(p2_ifg);

// Fake SPI registers
extern reg(UCA0CTL1); extern reg(UCA0CTL0); extern reg(UCA0BR0); extern reg(UCA0BR1);
extern reg(UCA1CTL1); extern reg(UCA1CTL0); extern reg(UCA1BR0); extern reg(UCA1BR1);
extern reg(UCB0CTL1); extern reg(UCB0CTL0); extern reg(UCB0BR0); extern reg(UCB0BR1);
extern reg(UCB1CTL1); extern reg(UCB1CTL0); extern reg(UCB1BR0); extern reg(UCB1BR1);
extern reg(UCA0TXBUF); extern reg(UCA0RXBUF); extern reg(UCA1TXBUF); extern reg(UCA1RXBUF);
extern reg(UCB0TXBUF); extern reg(UCB0RXBUF); extern reg(UCB1TXBUF); extern reg(UCB1RXBUF);

// Aliases for the unit tests
#define spi1_tx_buf UCA0TXBUF
#define spi1_rx_buf UCA0RXBUF
#define spi2_tx_buf UCA1TXBUF
#define spi2_rx_buf UCA1RXBUF
#define spi3_tx_buf UCB0TXBUF
#define spi3_rx_buf UCB0RXBUF
#define spi4_tx_buf UCB1TXBUF
#define spi4_rx_buf UCB1RXBUF

#endif







#endif
