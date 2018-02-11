/**
 * Pin Definitions for the MSP430F5529
 *
 * Authors: Michael Rouse
 */
#include "../fixture.h"
#include "msp430f5529_registers.h"

#ifndef UNIT_TEST
	#include <msp430f5529.h>
#endif

/* Register Pins and Ports */
REGISTER_PINS(80);
REGISTER_PORTS(1, 2, 3, 4, 5, 6, 7, 8, J);


/* Assign Port Bits to Pins *
REGISTER_PINS_FOR_PORT(1, 21, 22, 23, 24, 25, 26, 27, 28);
REGISTER_PINS_FOR_PORT(2, 29, 30, 31, 32, 33, 34, 35, 36);
REGISTER_PINS_FOR_PORT(3, 37, 38, 39, 40, 41, 42, 43, 44);
REGISTER_PINS_FOR_PORT(4, 45, 46, 47, 48, 51, 52, 53, 54);
REGISTER_PINS_FOR_PORT(5, 9, 10, 69, 70, 12, 13, 55, 56);
REGISTER_PINS_FOR_PORT(6, 77, 78, 79, 80, 1, 2, 3, 4 );
REGISTER_PINS_FOR_PORT(7, 5, 6, 7, 8, 57, 58, 59, 60);
REGISTER_PINS_FOR_PORT(8, 15, 16, 17);
REGISTER_PINS_FOR_PORT(J, 72, 73, 75, 75);*/


/* Configure Registers for the Ports */
SET_PORT_REGISTERS(1, P1DIR_REG, P1OUT_REG, P1IN_REG, P1SEL_REG, P1IES_REG, P1IE_REG, P1IFG_REG);
SET_PORT_REGISTERS(2, P2DIR_REG, P2OUT_REG, P2IN_REG, P2SEL_REG, P2IES_REG, P2IE_REG, P2IFG_REG);
SET_PORT_REGISTERS(3, P3DIR_REG, P3OUT_REG, P3IN_REG, P3SEL_REG, NO_REGISTER, NO_REGISTER, NO_REGISTER);
SET_PORT_REGISTERS(4, P4DIR_REG, P4OUT_REG, P4IN_REG, P4SEL_REG, NO_REGISTER, NO_REGISTER, NO_REGISTER);
SET_PORT_REGISTERS(5, P5DIR_REG, P5OUT_REG, P5IN_REG, P5SEL_REG, NO_REGISTER, NO_REGISTER, NO_REGISTER);
SET_PORT_REGISTERS(6, P6DIR_REG, P6OUT_REG, P6IN_REG, P6SEL_REG, NO_REGISTER, NO_REGISTER, NO_REGISTER);
SET_PORT_REGISTERS(7, P7DIR_REG, P7OUT_REG, P7IN_REG, P7SEL_REG, NO_REGISTER, NO_REGISTER, NO_REGISTER);
SET_PORT_REGISTERS(8, P8DIR_REG, P8OUT_REG, P8IN_REG, P8SEL_REG, NO_REGISTER, NO_REGISTER, NO_REGISTER);
SET_PORT_REGISTERS(J, PJDIR_REG, PJOUT_REG, PJIN_REG, NO_REGISTER, NO_REGISTER, NO_REGISTER, NO_REGISTER);

/* SPI BUSES */
REGISTER_SPI_BUSES(4);


/* Interrupts */
REGISTER_INTERRUPTABLE_PORTS(
  (PORT1, PORT1_VECTOR),
  (PORT2, PORT2_VECTOR)
);
