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

REGISTER_PORTS(
  (1, (&P1DIR), (&P1OUT), (&P1IN), (&P1SEL), (&P1IES), (&P1IE), (&P1IFG)),
  (2, (&P2DIR), (&P2OUT), (&P2IN), (&P2SEL), (&P2IES), (&P2IE), (&P2IFG)),
  (3, (&P3DIR), (&P3OUT), (&P3IN), (&P3SEL)),
  (4, (&P4DIR), (&P4OUT), (&P4IN), (&P4SEL)),
  (5, (&P5DIR), (&P5OUT), (&P5IN), (&P5SEL)),
  (6, (&P6DIR), (&P6OUT), (&P6IN), (&P6SEL)),
  (7, (&P7DIR), (&P7OUT), (&P7IN), (&P7SEL)),
  (8, (&P8DIR), (&P8OUT), (&P8IN), (&P8SEL)),
  (J, (&PJDIR), (&PJOUT), (&PJIN))
);


/* Assign Port Bits to Pins */
REGISTER_PINS_FOR_PORT(
  (1, 21, 22, 23, 24, 25, 26, 27, 28),
  (2, PIN29, 30, 31, 32, 33, 34, 35, 36),
  (3, 37, 38, 39, 40, 41, 42, 43, 44),
  (4, 45, 46, 47, 48, 51, 52, 53, 54),
  (5, 9, 10, 69, 70, 12, 13, 55, 56),
  (6, 77, 78, 79, 80, 1, 2, 3, 4 ),
  (7, 5, 6, 7, 8, 57, 58, 59, 60),
  (8, 15, 16, 17),
  (J, 72, 73, 75, 75)
);


/* SPI BUSES */
REGISTER_SPI_BUSES(4);


/* Interrupts */
REGISTER_INTERRUPTABLE_PORTS(
  (PORT1, PORT1_VECTOR),
  (PORT2, PORT2_VECTOR)
);
