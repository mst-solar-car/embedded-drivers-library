/**
 * This file contains all the arrays needed to map a value like P2_6 to the proper port and bit
 * for use in functions like setInput() or setOutput()
 *
 * Author: Michael Rouse
 */
#ifndef __MICROCONTROLLER__
#define __MICROCONTROLLER__

#include <msp430f5529.h>
#include "../microcontroller.h"


// Desired clock frequency (in Hz)
#define MICROCONTROLLER_CLOCK   20000000 



// Watchdog 
#define watchdog_disable()  WDTCTL = WDTPW + WDTHOLD


// Interrupts 
#define enable_interrupts()  __enable_interrupt();



// Port names mapped to an integer for use in an array
#define PORT1     1
#define PORT2     2
#define PORT3     3
#define PORT4     4
#define PORT5     5
#define PORT6     6
#define PORT7     7
#define PORT8     8
#define PORTJ     9


// Directives for things like PINx and PX_B
#define PIN0      0
#define PIN1      1
#define PIN2      2
#define PIN3      3
#define PIN4      4
#define PIN5      5
#define PIN6      6
#define PIN7      7
#define PIN8      8
#define PIN9      9
#define PIN10    10
#define PIN11    11
#define PIN12    12
#define PIN13    13
#define PIN14    14
#define PIN15    15
#define PIN16    16
#define PIN17    17
#define PIN18    18
#define PIN19    19
#define PIN20    20
#define PIN21    21
#define PIN22    22
#define PIN23    23
#define PIN24    24
#define PIN25    25
#define PIN26    26
#define PIN27    27
#define PIN28    28
#define PIN29    29
#define PIN30    30
#define PIN31    31
#define PIN32    32
#define PIN33    33
#define PIN34    34
#define PIN35    35
#define PIN36    36
#define PIN37    37
#define PIN38    38
#define PIN39    39
#define PIN40    40
#define PIN41    41
#define PIN42    42
#define PIN43    43
#define PIN44    44
#define PIN45    45
#define PIN46    46
#define PIN47    47
#define PIN48    48
#define PIN49    49
#define PIN50    50
#define PIN51    51
#define PIN52    52
#define PIN53    53
#define PIN54    54
#define PIN55    55
#define PIN56    56
#define PIN57    57
#define PIN58    58
#define PIN59    59
#define PIN60    60
#define PIN61    61
#define PIN62    62
#define PIN63    63
#define PIN64    64
#define PIN65    65
#define PIN66    66
#define PIN67    67
#define PIN68    68
#define PIN69    69
#define PIN70    70
#define PIN71    71
#define PIN72    72
#define PIN73    73
#define PIN74    74
#define PIN75    75
#define PIN76    76
#define PIN77    77
#define PIN78    78
#define PIN79    79
#define PIN80    80

// Port 1
#define P1_0      PIN21
#define P1_1      PI22
#define P1_2      PIN23
#define P1_3      PIN24
#define P1_4      PIN25
#define P1_5      PIN26
#define P1_6      PIN27
#define P1_7      PIN28

// Port 2
#define P2_0      PIN29
#define P2_1      PIN30
#define P2_2      PIN31
#define P2_3      PIN32
#define P2_4      PIN33
#define P2_5      PIN34
#define P2_6      PIN35
#define P2_7      PIN36

// Port 3
#define P3_0      PIN37
#define P3_1      PIN38
#define P3_2      PIN39
#define P3_3      PIN40
#define P3_4      PIN41
#define P3_5      PIN42
#define P3_6      PIN43
#define P3_7      PIN44

// Port 4
#define P4_0      PIN45
#define P4_1      PIN46
#define P4_2      PIN47
#define P4_3      PIN48
#define P4_4      PIN51
#define P4_5      PIN52
#define P4_6      PIN53
#define P4_7      PIN54

// Port 5
#define P5_0      PIN9
#define P5_1      PIN10
#define P5_2      PIN69
#define P5_3      PIN70
#define P5_4      PIN12
#define P5_5      PIN13
#define P5_6      PIN55
#define P5_7      PIN56

// Port 6
#define P6_0      PIN77
#define P6_1      PIN78
#define P6_2      PIN79
#define P6_3      PIN80
#define P6_4      PIN1
#define P6_5      PIN2
#define P6_6      PIN3
#define P6_7      PIN4

// Port 7
#define P7_0      PIN5
#define P7_1      PIN6
#define P7_2      PIN7
#define P7_3      PIN8
#define P7_4      PIN57
#define P7_5      PIN58
#define P7_6      PIN59
#define P7_7      PIN60

// Port 8
#define P8_0      PIN15
#define P8_1      PIN16
#define P8_2      PIN17

// Port J
#define PJ_0      PIN72
#define PJ_1      PIN73
#define PJ_2      PIN74
#define PJ_3      PIN75






/**
 * Register addresses for MSP430F5529
 * These can be found using the datasheet or the msp430f5529_symbols.ld linker script
 */
#define P1IN_REG        0x0200
#define P1OUT_REG       0x0202
#define P1DIR_REG       0x0204
#define P1SEL_REG       0x020A
#define P1IES_REG       0x0218
#define P1IE_REG        0x021A
#define P1IFG_REG       0x021C

#define P2IN_REG        0x0201
#define P2OUT_REG       0x0203
#define P2DIR_REG       0x0205
#define P2SEL_REG       0x020B
#define P2IES_REG       0x0219
#define P2IE_REG        0x021B
#define P2IFG_REG       0x021D

#define P3IN_REG        0x0220
#define P3OUT_REG       0x0222
#define P3DIR_REG       0x0224
#define P3SEL_REG       0x022A

#define P4IN_REG        0x0221
#define P4OUT_REG       0x0223
#define P4DIR_REG       0x0225
#define P4SEL_REG       0x022B

#define P5IN_REG        0x0240
#define P5OUT_REG       0x0242
#define P5DIR_REG       0x0244
#define P5SEL_REG       0x024A

#define P6IN_REG        0x0241
#define P6OUT_REG       0x0243
#define P6DIR_REG       0x0245
#define P6SEL_REG       0x025B

#define P7IN_REG        0x0260
#define P7OUT_REG       0x0262
#define P7DIR_REG       0x0264
#define P7SEL_REG       0x026A

#define P8IN_REG        0x0261
#define P8OUT_REG       0x0262
#define P8DIR_REG       0x0265
#define P8SEL_REG       0x026B

#define PJIN_REG        0x0320
#define PJOUT_REG       0x0322
#define PJDIR_REG       0x0324











#endif
