/**
 * Register Definitions
 *
 * Authors: Michael Rouse
 */
#ifndef __MSP430F5529_REGISTERS__
#define __MSP430F5529_REGISTERS__

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

#endif
