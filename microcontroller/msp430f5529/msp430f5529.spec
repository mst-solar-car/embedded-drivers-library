/**
 * Pin Definitions for the MSP430F5529
 *
 * Authors: Michael Rouse
 */
#include "../fixture.h"

/* System */
CLOCK_SPEED_HZ(20000000);

/* Register Pins and Ports */
REGISTER_PINS(80);
REGISTER_PORTS(1, 2, 3, 4, 5, 6, 7, 8, J);


/* Configure Registers for the Ports */
SET_PORT_REGISTERS(1, (&P1DIR), (&P1OUT), (&P1IN), (&P1SEL), (&P1IES), (&P1IE), (&P1IFG));
SET_PORT_REGISTERS(2, (&P2DIR), (&P2OUT), (&P2IN), (&P2SEL), (&P2IES), (&P2IE), (&P2IFG));
SET_PORT_REGISTERS(3, (&P3DIR), (&P3OUT), (&P3IN), (&P3SEL), NO_REGISTER, NO_REGISTER, NO_REGISTER);
SET_PORT_REGISTERS(4, (&P4DIR), (&P4OUT), (&P4IN), (&P4SEL), NO_REGISTER, NO_REGISTER, NO_REGISTER);
SET_PORT_REGISTERS(5, (&P5DIR), (&P5OUT), (&P5IN), (&P5SEL), NO_REGISTER, NO_REGISTER, NO_REGISTER);
SET_PORT_REGISTERS(6, (&P6DIR), (&P6OUT), (&P6IN), (&P6SEL), NO_REGISTER, NO_REGISTER, NO_REGISTER);
SET_PORT_REGISTERS(7, (&P7DIR), (&P7OUT), (&P7IN), (&P7SEL), NO_REGISTER, NO_REGISTER, NO_REGISTER);
SET_PORT_REGISTERS(8, (&P8DIR), (&P8OUT), (&P8IN), (&P8SEL), NO_REGISTER, NO_REGISTER, NO_REGISTER);
SET_PORT_REGISTERS(J, (&PJDIR), (&PJOUT), (&PJIN), NO_REGISTER, NO_REGISTER, NO_REGISTER, NO_REGISTER);

/* Assign Port Bits to Pins */
REGISTER_PINS_FOR_PORT(1, 21, 22, 23, 24, 25, 26, 27, 28);
REGISTER_PINS_FOR_PORT(2, PIN29, 30, 31, 32, 33, 34, 35, 36);
REGISTER_PINS_FOR_PORT(3, 37, 38, 39, 40, 41, 42, 43, 44);
REGISTER_PINS_FOR_PORT(4, 45, 46, 47, 48, 51, 52, 53, 54);
REGISTER_PINS_FOR_PORT(5, 9, 10, 69, 70, 12, 13, 55, 56);
REGISTER_PINS_FOR_PORT(6, 77, 78, 79, 80, 1, 2, 3, 4 );
REGISTER_PINS_FOR_PORT(7, 5, 6, 7, 8, 57, 58, 59, 60);
REGISTER_PINS_FOR_PORT(8, 15, 16, 17);
REGISTER_PINS_FOR_PORT(J, 72, 73, 75, 75);


/* SPI BUSES */
REGISTER_SPI_BUSES(4);


/* Interrupts */
REGISTER_INTERRUPTABLE_PORTS(
  (PORT1, PORT1_VECTOR),
  (PORT2, PORT2_VECTOR)
);
