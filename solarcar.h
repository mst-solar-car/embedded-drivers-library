/**
 * Solar Car MSP430F5529 Library
 * This library is designed to make writing code simpler for the MSP430F5529.
 *
 * Authors: Michael Rouse
 */
#ifndef __SOLARCAR_H__
#define __SOLARCAR_H__

#include <msp430.h>


/**
 * Data Types
 */
#define TRUE      1
#define True      TRUE
#define true      TRUE

#define FALSE     0
#define False     FALSE
#define false

#define NULL      0x00
#define NIL       NULL

// Type aliases
typedef char int8_t;
typedef unsigned char uint8_t;

typedef short int16_t;
typedef unsigned short uint16_t;

typedef long int32_t;
typedef unsigned long uint32_t;

typedef long long int64_t;
typedef unsigned long long uint65_t;

typedef char bool;

typedef volatile unsigned int vuint32_t;

typedef union group_64_t {
   float data_fp[2];           // Holds floating point
   unsigned char data_u8[8];   // Holds 8 unsigned bits
   char data_8[8];              // Holds 8 signed bits
   unsigned int data_u16[4];   // Holds 16 unsigned bits
   int data_16[4];             // Holds 16 bits
   unsigned long data_u32[2];  // Holds 32 unsigned bits
   long data_32[2];            // Holds 32 bits
} group_64;


// Struct for a CAN Message
typedef struct can_message_t {
  unsigned int  address;
  unsigned int  status;
  group_64      data;
} can_message;


/**
 * Basic definitions
 */
#define INPUT   0
#define OUTPUT  1

#define LOW     0
#define HIGH    1


#define NO_PIN      PORT_NONE
#define NO_REGISTER PORT_NONE
#define NO_PORT     PORT_NONE

// Misc. Pins
#define PIN11   PORT_NONE
#define PIN14   PORT_NONE
#define PIN18   PORT_NONE
#define PIN19   PORT_NONE
#define PIN20   PORT_NONE
#define PIN49   PORT_NONE
#define PIN50   PORT_NONE
#define PIN61   PORT_NONE
#define PIN62   PORT_NONE
#define PIN64   PORT_NONE
#define PIN63   PORT_NONE
#define PIN65   PORT_NONE
#define PIN66   PORT_NONE
#define PIN67   PORT_NONE
#define PIN68   PORT_NONE
#define PIN71   PORT_NONE
#define PIN76   PORT_NONE



// This Port (PORT 0) is definted to be compatible with everything else
#define PORT_NONE   0
#define SEL_0       NO_REGISTER
#define DIR_0       NO_REGISTER
#define IN_0        NO_REGISTER
#define OUT_0       NO_REGISTER
#define IES_0       NO_REGISTER
#define IFG_0       NO_REGISTER
#define IE_0        NO_REGISTER
#define BIT_0       BIT0

/**
 * Port 1
 */
// P1.0
#define PIN21       PORT1_0
#define P1_0        PORT1_0
#define PORT1_0     10
#define SEL_10      P1SEL
#define DIR_10      P1DIR
#define IN_10       P1IN
#define OUT_10      P1OUT
#define IES_10      P1IES
#define IFG_10      P1IFG
#define IE_10       P1IE
#define BIT_10      BIT0

// P1.1
#define PIN22       PORT1_1
#define P1_1        PORT1_1
#define PORT1_1     11
#define SEL_11      P1SEL
#define DIR_11      P1DIR
#define IN_11       P1IN
#define OUT_11      P1OUT
#define IES_11      P1IES
#define IFG_11      P1IFG
#define IE_11       P1IE
#define BIT_11      BIT1

// P1.2
#define PIN23       PORT1_2
#define P1_2        PORT1_2
#define PORT1_2     12
#define SEL_12      P1SEL
#define DIR_12      P1DIR
#define IN_12       P1IN
#define OUT_12      P1OUT
#define IES_12      P1IES
#define IFG_12      P1IFG
#define IE_12       P1IE
#define BIT_12      BIT2

// P1.3
#define PIN24       PORT1_3
#define PORT1_3     13
#define SEL_13      P1SEL
#define DIR_13      P1DIR
#define IN_13       P1IN
#define OUT_13      P1OUT
#define IES_13      P1IES
#define IFG_13      P1IFG
#define IE_13       P1IE
#define BIT_13      BIT3

// P1.4
#define PIN25       PORT1_4
#define PORT1_4     14
#define SEL_14      P1SEL
#define DIR_14      P1DIR
#define IN_14       P1IN
#define OUT_14      P1OUT
#define IES_14      P1IES
#define IFG_14      P1IFG
#define IE_14       P1IE
#define BIT_14      BIT4

// P1.5
#define PIN26       PORT1_5
#define PORT1_5     15
#define SEL_15      P1SEL
#define DIR_15      P1DIR
#define IN_15       P1IN
#define OUT_15      P1OUT
#define IES_15      P1IES
#define IFG_15      P1IFG
#define IE_15       P1IE
#define BIT_15      BIT5

// P1.6
#define PIN27       PORT1_6
#define PORT1_6     16
#define SEL_16      P1SEL
#define DIR_16      P1DIR
#define IN_16       P1IN
#define OUT_16      P1OUT
#define IES_16      P1IES
#define IFG_16      P1IFG
#define IE_16       P1IE
#define BIT_16      BIT6

// P1.7
#define PIN28       PORT1_7
#define PORT1_7     17
#define SEL_17      P1SEL
#define DIR_17      P1DIR
#define IN_17       P1IN
#define OUT_17      P1OUT
#define IES_17      P1IES
#define IFG_17      P1IFG
#define IE_17       P1IE
#define BIT_17      BIT7


/**
 * Port 2
 */
// P2.0
#define PIN29       PORT2_0
#define P2_0        PORT2_0
#define PORT2_0     20
#define SEL_20      P2SEL
#define DIR_20      P2DIR
#define IN_20       P2IN
#define OUT_20      P2OUT
#define IES_20      P2IES
#define IFG_20      P2IFG
#define IE_20       P2IE
#define BIT_20      BIT0

// P2.1
#define PIN30       PORT2_1
#define P2_1        PORT2_1
#define PORT2_1     21
#define SEL_21      P2SEL
#define DIR_21      P2DIR
#define IN_21       P2IN
#define OUT_21      P2OUT
#define IES_21      P2IES
#define IFG_21      P2IFG
#define IE_21       P2IE
#define BIT_21      BIT1

// P2.2
#define PIN31       PORT2_2
#define P2_2        PORT2_2
#define PORT2_2     22
#define SEL_22      P2SEL
#define DIR_22      P2DIR
#define IN_22       P2IN
#define OUT_22      P2OUT
#define IES_22      P2IES
#define IFG_22      P2IFG
#define IE_22       P2IE
#define BIT_22      BIT2

// P2.3
#define PIN32       PORT2_3
#define P2_3        PORT2_3
#define PORT2_3     23
#define SEL_23      P2SEL
#define DIR_23      P2DIR
#define IN_23       P2IN
#define OUT_23      P2OUT
#define IES_23      P2IES
#define IFG_23      P2IFG
#define IE_23       P2IE
#define BIT_23      BIT3

// P2.4
#define PIN33       PORT2_4
#define P2_4        PORT2_4
#define PORT2_4     24
#define SEL_24      P2SEL
#define DIR_24      P2DIR
#define IN_24       P2IN
#define OUT_24      P2OUT
#define IES_24      P2IES
#define IFG_24      P2IFG
#define IE_24       P2IE
#define BIT_24      BIT4

// P2.5
#define PIN34       PORT2_5
#define P2_5        PORT2_5
#define PORT2_5     25
#define SEL_25      P2SEL
#define DIR_25      P2DIR
#define IN_25       P2IN
#define OUT_25      P2OUT
#define IES_25      P2IES
#define IFG_25      P2IFG
#define IE_25       P2IE
#define BIT_25      BIT5

// P2.6
#define PIN35       PORT2_6
#define P2_6        PORT2_6
#define PORT2_6     26
#define SEL_26      P2SEL
#define DIR_26      P2DIR
#define IN_26       P2IN
#define OUT_26      P2OUT
#define IES_26      P2IES
#define IFG_26      P2IFG
#define IE_26       P2IE
#define BIT_26      BIT6

// P2.7
#define PIN36       PORT2_7
#define P2_7        PORT2_7
#define PORT2_7     27
#define SEL_27      P2SEL
#define DIR_27      P2DIR
#define IN_27       P2IN
#define OUT_27      P2OUT
#define IES_27      P2IES
#define IFG_27      P2IFG
#define IE_27       P2IE
#define BIT_27      BIT7


/**
 * Port 3
 */
// P3.0
#define PIN37       PORT3_0
#define P3_0        PORT3_0
#define PORT3_0     30
#define SEL_30      P3SEL
#define DIR_30      P3DIR
#define IN_30       P3IN
#define OUT_30      P3OUT
#define IES_30      NO_REGISTER
#define IFG_30      NO_REGISTER
#define IE_30       NO_REGISTER
#define BIT_30      BIT0

// P3.1
#define PIN38       PORT3_1
#define P3_1        PORT3_1
#define PORT3_1     31
#define SEL_31      P3SEL
#define DIR_31      P3DIR
#define IN_31       P3IN
#define OUT_31      P3OUT
#define IES_31      NO_REGISTER
#define IFG_31      NO_REGISTER
#define IE_31       NO_REGISTER
#define BIT_31      BIT1

// P3.2
#define PIN39       PORT3_2
#define P3_2        PORT3_2
#define PORT3_2     32
#define SEL_32      P3SEL
#define DIR_32      P3DIR
#define IN_32       P3IN
#define OUT_32      P3OUT
#define IES_32      NO_REGISTER
#define IFG_32      NO_REGISTER
#define IE_32       NO_REGISTER
#define BIT_32      BIT2

// P3.3
#define PIN40       PORT3_3
#define P3_3        PORT3_3
#define PORT3_3     33
#define SEL_33      P3SEL
#define DIR_33      P3DIR
#define IN_33       P3IN
#define OUT_33      P3OUT
#define IES_33      NO_REGISTER
#define IFG_33      NO_REGISTER
#define IE_33       NO_REGISTER
#define BIT_33      BIT3

// P3.4
#define PIN41       PORT3_4
#define P3_4        PORT3_4
#define PORT3_4     34
#define SEL_34      P3SEL
#define DIR_34      P3DIR
#define IN_34       P3IN
#define OUT_34      P3OUT
#define IES_34      NO_REGISTER
#define IFG_34      NO_REGISTER
#define IE_34       NO_REGISTER
#define BIT_34      BIT4

// P3.5
#define PIN42       PORT3_5
#define P3_5        PORT3_5
#define PORT3_5     35
#define SEL_35      P3SEL
#define DIR_35      P3DIR
#define IN_35       P3IN
#define OUT_35      P3OUT
#define IES_35      NO_REGISTER
#define IFG_35      NO_REGISTER
#define IE_35       NO_REGISTER
#define BIT_35      BIT5

// P3.6
#define PIN43       PORT3_6
#define P3_6        PORT3_6
#define PORT3_6     36
#define SEL_36      P3SEL
#define DIR_36      P3DIR
#define IN_36       P3IN
#define OUT_36      P3OUT
#define IES_36      NO_REGISTER
#define IFG_36      NO_REGISTER
#define IE_36       NO_REGISTER
#define BIT_36      BIT6

// P3.7
#define PIN44       PORT3_7
#define P3_7        PORT3_7
#define PORT3_7     37
#define SEL_37      P3SEL
#define DIR_37      P3DIR
#define IN_37       P3IN
#define OUT_37      P3OUT
#define IES_37      NO_REGISTER
#define IFG_37      NO_REGISTER
#define IE_37       NO_REGISTER
#define BIT_37      BIT7


/**
 * Port 4
 */
// P4.0
#define PIN45       PORT4_0
#define P4_0        PORT4_0
#define PORT4_0     40
#define SEL_40      P4SEL
#define DIR_40      P4DIR
#define IN_40       P4IN
#define OUT_40      P4OUT
#define IES_40      NO_REGISTER
#define IFG_40      NO_REGISTER
#define IE_40       NO_REGISTER
#define BIT_40      BIT0

// P4.1
#define PIN46       PORT4_1
#define P4_1        PORT4_1
#define PORT4_1     41
#define SEL_41      P4SEL
#define DIR_41      P4DIR
#define IN_41       P4IN
#define OUT_41      P4OUT
#define IES_41      NO_REGISTER
#define IFG_41      NO_REGISTER
#define IE_41       NO_REGISTER
#define BIT_41      BIT1

// P4.2
#define PIN47       PORT4_2
#define P4_2        PORT4_2
#define PORT4_2     42
#define SEL_42      P4SEL
#define DIR_42      P4DIR
#define IN_42       P4IN
#define OUT_42      P4OUT
#define IES_42      NO_REGISTER
#define IFG_42      NO_REGISTER
#define IE_42       NO_REGISTER
#define BIT_42      BIT2

// P4.3
#define PIN48       PORT4_3
#define P4_3        PORT4_3
#define PORT4_3     43
#define SEL_43      P4SEL
#define DIR_43      P4DIR
#define IN_43       P4IN
#define OUT_43      P4OUT
#define IES_43      NO_REGISTER
#define IFG_43      NO_REGISTER
#define IE_43       NO_REGISTER
#define BIT_43      BIT3

// P4.4
#define PIN51       PORT4_4
#define P4_4        PORT4_4
#define PORT4_4     44
#define SEL_44      P4SEL
#define DIR_44      P4DIR
#define IN_44       P4IN
#define OUT_44      P4OUT
#define IES_44      NO_REGISTER
#define IFG_44      NO_REGISTER
#define IE_44       NO_REGISTER
#define BIT_44      BIT4

// P4.5
#define PIN52       PORT4_5
#define P4_5        PORT4_5
#define PORT4_5     45
#define SEL_45      P4SEL
#define DIR_45      P4DIR
#define IN_45       P4IN
#define OUT_45      P4OUT
#define IES_45      NO_REGISTER
#define IFG_45      NO_REGISTER
#define IE_45       NO_REGISTER
#define BIT_45      BIT5

// P4.6
#define PIN53       PORT4_6
#define P4_6        PORT4_6
#define PORT4_6     46
#define SEL_46      P4SEL
#define DIR_46      P4DIR
#define IN_46       P4IN
#define OUT_46      P4OUT
#define IES_46      NO_REGISTER
#define IFG_46      NO_REGISTER
#define IE_46       NO_REGISTER
#define BIT_46      BIT6

// P4.7
#define PIN54       PORT4_7
#define P4_7        PORT4_7
#define PORT4_7     47
#define SEL_47      P4SEL
#define DIR_47      P4DIR
#define IN_47       P4IN
#define OUT_47      P4OUT
#define IES_47      NO_REGISTER
#define IFG_47      NO_REGISTER
#define IE_47       NO_REGISTER
#define BIT_47      BIT7


/**
 * Port 5
 */
// P5.0
#define PIN9        PORT5_0
#define P5_0        PORT5_0
#define PORT5_0     50
#define SEL_50      P5SEL
#define DIR_50      P5DIR
#define IN_50       P5IN
#define OUT_50      P5OUT
#define IES_50      NO_REGISTER
#define IFG_50      NO_REGISTER
#define IE_50       NO_REGISTER
#define BIT_50      BIT0

// P5.1
#define PIN10       PORT5_1
#define P5_1        PORT5_1
#define PORT5_1     51
#define SEL_51      P5SEL
#define DIR_51      P5DIR
#define IN_51       P5IN
#define OUT_51      P5OUT
#define IES_51      NO_REGISTER
#define IFG_51      NO_REGISTER
#define IE_51       NO_REGISTER
#define BIT_51      BIT1

// P5.2
#define PIN69       PORT5_2
#define P5_2        PORT5_2
#define PORT5_2     52
#define SEL_52      P5SEL
#define DIR_52      P5DIR
#define IN_52       P5IN
#define OUT_52      P5OUT
#define IES_52      NO_REGISTER
#define IFG_52      NO_REGISTER
#define IE_52       NO_REGISTER
#define BIT_52      BIT2

// P5.3
#define PIN70       PORT5_3
#define P5_3        PORT5_3
#define PORT5_3     53
#define SEL_53      P5SEL
#define DIR_53      P5DIR
#define IN_53       P5IN
#define OUT_53      P5OUT
#define IES_53      NO_REGISTER
#define IFG_53      NO_REGISTER
#define IE_53       NO_REGISTER
#define BIT_53      BIT3

// P5.4
#define PIN12       PORT5_4
#define P5_4        PORT5_4
#define PORT5_4     54
#define SEL_54      P5SEL
#define DIR_54      P5DIR
#define IN_54       P5IN
#define OUT_54      P5OUT
#define IES_54      NO_REGISTER
#define IFG_54      NO_REGISTER
#define IE_54       NO_REGISTER
#define BIT_54      BIT4

// P5.5
#define PIN13       PORT5_5
#define P5_5        PORT5_5
#define PORT5_5     55
#define SEL_55      P5SEL
#define DIR_55      P5DIR
#define IN_55       P5IN
#define OUT_55      P5OUT
#define IES_55      NO_REGISTER
#define IFG_55      NO_REGISTER
#define IE_55       NO_REGISTER
#define BIT_55      BIT5

// P5.6
#define PIN55       PORT5_6
#define P5_6        PORT5_6
#define PORT5_6     56
#define SEL_56      P5SEL
#define DIR_56      P5DIR
#define IN_56       P5IN
#define OUT_56      P5OUT
#define IES_56      NO_REGISTER
#define IFG_56      NO_REGISTER
#define IE_56       NO_REGISTER
#define BIT_56      BIT6

// P5.7
#define PIN56       PORT5_7
#define P5_7        PORT5_7
#define PORT5_7     57
#define SEL_57      P5SEL
#define DIR_57      P5DIR
#define IN_57       P5IN
#define OUT_57      P5OUT
#define IES_57      NO_REGISTER
#define IFG_57      NO_REGISTER
#define IE_57       NO_REGISTER
#define BIT_57      BIT7


/**
 * Port 6
 */
// P6.0
#define PIN77       PORT6_0
#define P6_0        PORT6_0
#define PORT6_0     60
#define SEL_60      P6SEL
#define DIR_60      P6DIR
#define IN_60       P6IN
#define OUT_60      P6OUT
#define IES_60      NO_REGISTER
#define IFG_60      NO_REGISTER
#define IE_60       NO_REGISTER
#define BIT_60      BIT0

// P6.1
#define PIN78       PORT6_1
#define P6_1        PORT6_1
#define PORT6_1     61
#define SEL_61      P6SEL
#define DIR_61      P6DIR
#define IN_61       P6IN
#define OUT_61      P6OUT
#define IES_61      NO_REGISTER
#define IFG_61      NO_REGISTER
#define IE_61       NO_REGISTER
#define BIT_61      BIT1

// P6.2
#define PIN79       PORT6_2
#define P6_2        PORT6_2
#define PORT6_2     62
#define SEL_62      P6SEL
#define DIR_62      P6DIR
#define IN_62       P6IN
#define OUT_62      P6OUT
#define IES_62      NO_REGISTER
#define IFG_62      NO_REGISTER
#define IE_62       NO_REGISTER
#define BIT_62      BIT2

// P6.3
#define PIN80       PORT6_3
#define P6_3        PORT6_3
#define PORT6_3     63
#define SEL_63      P6SEL
#define DIR_63      P6DIR
#define IN_63       P6IN
#define OUT_63      P6OUT
#define IES_63      NO_REGISTER
#define IFG_63      NO_REGISTER
#define IE_63       NO_REGISTER
#define BIT_63      BIT3

// P6.4
#define PIN1        PORT6_4
#define P6_4        PORT6_4
#define PORT6_4     64
#define SEL_64      P6SEL
#define DIR_64      P6DIR
#define IN_64       P6IN
#define OUT_64      P6OUT
#define IES_64      NO_REGISTER
#define IFG_64      NO_REGISTER
#define IE_64       NO_REGISTER
#define BIT_64      BIT4

// P6.5
#define PIN2        PORT6_5
#define P6_5        PORT6_5
#define PORT6_5     65
#define SEL_65      P6SEL
#define DIR_65      P6DIR
#define IN_65       P6IN
#define OUT_65      P6OUT
#define IES_65      NO_REGISTER
#define IFG_65      NO_REGISTER
#define IE_65       NO_REGISTER
#define BIT_65      BIT5

// P6.6
#define PIN3        PORT6_6
#define P6_6        PORT6_6
#define PORT6_6     66
#define SEL_66      P6SEL
#define DIR_66      P6DIR
#define IN_66       P6IN
#define OUT_66      P6OUT
#define IES_66      NO_REGISTER
#define IFG_66      NO_REGISTER
#define IE_66       NO_REGISTER
#define BIT_66      BIT6

// P6.7
#define PIN4        PORT6_7
#define P6_7        PORT6_7
#define PORT6_7     67
#define SEL_67      P6SEL
#define DIR_67      P6DIR
#define IN_67       P6IN
#define OUT_67      P6OUT
#define IES_67      NO_REGISTER
#define IFG_67      NO_REGISTER
#define IE_67       NO_REGISTER
#define BIT_67      BIT7


/**
 * Port 7
 */
// P7.0
#define PIN5        PORT7_0
#define P7_0        PORT7_0
#define PORT7_0     70
#define SEL_70      P7SEL
#define DIR_70      P7DIR
#define IN_70       P7IN
#define OUT_70      P7OUT
#define IES_70      NO_REGISTER
#define IFG_70      NO_REGISTER
#define IE_70       NO_REGISTER
#define BIT_70      BIT0

// P7.1
#define PIN6        PORT7_1
#define P7_1        PORT7_1
#define PORT7_1     71
#define SEL_71      P7SEL
#define DIR_71      P7DIR
#define IN_71       P7IN
#define OUT_71      P7OUT
#define IES_71      NO_REGISTER
#define IFG_71      NO_REGISTER
#define IE_71       NO_REGISTER
#define BIT_71      BIT1

// P7.2
#define PIN7        PORT7_2
#define P7_2        PORT7_2
#define PORT7_2     72
#define SEL_72      P7SEL
#define DIR_72      P7DIR
#define IN_72       P7IN
#define OUT_72      P7OUT
#define IES_72      NO_REGISTER
#define IFG_72      NO_REGISTER
#define IE_72       NO_REGISTER
#define BIT_72      BIT2

// P7.3
#define PIN8        PORT7_3
#define P7_3        PORT7_3
#define PORT7_3     73
#define SEL_73      P7SEL
#define DIR_73      P7DIR
#define IN_73       P7IN
#define OUT_73      P7OUT
#define IES_73      NO_REGISTER
#define IFG_73      NO_REGISTER
#define IE_73       NO_REGISTER
#define BIT_73      BIT3

// P7.4
#define PIN57       PORT7_4
#define P7_4        PORT7_4
#define PORT7_4     74
#define SEL_74      P7SEL
#define DIR_74      P7DIR
#define IN_74       P7IN
#define OUT_74      P7OUT
#define IES_74      NO_REGISTER
#define IFG_74      NO_REGISTER
#define IE_74       NO_REGISTER
#define BIT_74      BIT4

// P7.5
#define PIN58       PORT7_5
#define P7_5        PORT7_5
#define PORT7_5     75
#define SEL_75      P7SEL
#define DIR_75      P7DIR
#define IN_75       P7IN
#define OUT_75      P7OUT
#define IES_75      NO_REGISTER
#define IFG_75      NO_REGISTER
#define IE_75       NO_REGISTER
#define BIT_75      BIT5

// P7.6
#define PIN59       PORT7_6
#define P7_6        PORT7_6
#define PORT7_6     76
#define SEL_76      P7SEL
#define DIR_76      P7DIR
#define IN_76       P7IN
#define OUT_76      P7OUT
#define IES_76      NO_REGISTER
#define IFG_76      NO_REGISTER
#define IE_76       NO_REGISTER
#define BIT_76      BIT6

// P7.7
#define PIN60       PORT7_7
#define P7_7        PORT7_7
#define PORT7_7     77
#define SEL_77      P7SEL
#define DIR_77      P7DIR
#define IN_77       P7IN
#define OUT_77      P7OUT
#define IES_77      NO_REGISTER
#define IFG_77      NO_REGISTER
#define IE_77       NO_REGISTER
#define BIT_77      BIT7


/**
 * Port 8
 */
// P8.0
#define PIN15       PORT8_0
#define P8_0        PORT8_0
#define PORT8_0     80
#define SEL_80      P8SEL
#define DIR_80      P8DIR
#define IN_80       P8IN
#define OUT_80      P8OUT
#define IES_80      NO_REGISTER
#define IFG_80      NO_REGISTER
#define IE_80       NO_REGISTER
#define BIT_80      BIT0

// P8.1
#define PIN16       PORT8_1
#define P8_1        PORT8_1
#define PORT8_1     81
#define SEL_81      P8SEL
#define DIR_81      P8DIR
#define IN_81       P8IN
#define OUT_81      P8OUT
#define IES_81      NO_REGISTER
#define IFG_81      NO_REGISTER
#define IE_81       NO_REGISTER
#define BIT_81      BIT1

// P8.2
#define PIN17       PORT8_2
#define P8_2        PORT8_2
#define PORT8_2     82
#define SEL_82      P8SEL
#define DIR_82      P8DIR
#define IN_82       P8IN
#define OUT_82      P8OUT
#define IES_82      NO_REGISTER
#define IFG_82      NO_REGISTER
#define IE_82       NO_REGISTER
#define BIT_82      BIT2


/**
 * Port J
 */
// PJ.0
#define PIN72       PORTJ_0
#define PJ_0        PORTJ_0
#define PORTJ_0     90
#define SEL_90      PJSEL
#define DIR_90      PJDIR
#define IN_90       PJIN
#define OUT_90      PJOUT
#define IES_90      NO_REGISTER
#define IFG_90      NO_REGISTER
#define IE_90       NO_REGISTER
#define BIT_90      BIT0

// PJ.1
#define PIN73       PORTJ_1
#define PJ_1        PORTJ_1
#define PORTJ_1     91
#define SEL_91      PJSEL
#define DIR_91      PJDIR
#define IN_91       PJIN
#define OUT_91      PJOUT
#define IES_91      NO_REGISTER
#define IFG_91      NO_REGISTER
#define IE_91       NO_REGISTER
#define BIT_91      BIT1

// PJ.2
#define PIN74       PORTJ_2
#define PJ_2        PORTJ_2
#define PORTJ_2     92
#define SEL_92      PJSEL
#define DIR_92      PJDIR
#define IN_92       PJIN
#define OUT_92      PJOUT
#define IES_92      NO_REGISTER
#define IFG_92      NO_REGISTER
#define IE_92       NO_REGISTER
#define BIT_92      BIT2

// PJ.3
#define PIN75       PORTJ_3
#define PJ_3        PORTJ_3
#define PORTJ_3     93
#define SEL_93      PJSEL
#define DIR_93      PJDIR
#define IN_93       PJIN
#define OUT_93      PJOUT
#define IES_93      NO_REGISTER
#define IFG_93      NO_REGISTER
#define IE_93       NO_REGISTER
#define BIT_93      BIT3




// TODO: Resistor Enable and Drive Strength

/**
 * Directives for converting alias to register
 * TODO: Explain why there are two for each, and what ## does
 */
// Selection registers
#define sel(pin)    sel_(pin)
#define sel_(pin)   SEL_ ## pin

// Direction registers
#define dir(pin)    dir_(pin)
#define dir_(pin)   DIR_ ## pin

// Input registers
#define in(pin)     in_(pin)
#define in_(pin)    IN_ ## pin

// Output registers
#define out(pin)    out_(pin)
#define out_(pin)   OUT_ ## pin

// Interrupt Edge Select registers
#define ies(pin)    ies_(pin)
#define ies_(pin)   IES_ ## pin

// Interrupt Flag registers
#define ifg(pin)    ifg_(pin)
#define ifg_(pin)   IFG_ ## pin

// Interrupt Enable registers
#define ie(pin)     ie_(pin)
#define ie_(pin)    IE_ ## pin

// Get what bit the register port is on
#define bit(pin)    bit_(pin)
#define bit_(pin)   BIT_ ## pin





/**
 * Directives to mark ports as INPUT or OUTPUT
 */
#define inputPin(pin)     dir(pin) &= ~bit(pin)   // Configures a pin for INPUT
#define setInput(pin)     inputPin(pin)           // inputPin alias

#define outputPin(pin)    dir(pin) |= bit(pin)    // Configures a pin for OUTPUT
#define setOutput(pin)    outputPin(pin)          // outputPin alias


/**
 * Directives for controlling pins
 */
#define setHigh(pin)      out(pin) |= bit(pin)    // Sets a pin HIGH
#define setPinHigh(pin)   setHigh(pin)            // Alias

#define setLow(pin)       out(pin) &= ~bit(pin)   // Sets a pin LOW
#define setPinLow(pin)    setLow(pin)             // Alias

#define toggle(pin)       out(pin) ^= bit(pin)    // Toggles a pin HIGH or LOW
#define togglePin(pin)    toggle(pin)             // Alias

#define read(pin)         (in(pin) & bit(pin))    // Reads value of bit in register
#define readPin(pin)      read(pin)               // Alias


/**
 * Checking Bits
 */
#define getBit(data, bit)   (data & bit)

#define isLow(data, bit)    (getBit(data, bit) != bit)
#define isHigh(data, bit)   (getBit(data, bit) == bit)

#define leftShift(bits, n)  ((uint8_t)(bits << n))
#define rightShift(bits, n) ((uint8_t)(bits >> n))


/**
 * Arduino-Like Aliases
 */
#define pinMode(pin, mode)        if (mode == INPUT) inputPin(pin); else outputPin(pin)
#define digitalWrite(pin, state)  if (state == HIGH) setHigh(pin);  else setLow(pin)
#define digitalRead(pin)          read(pin)



// Simple basic init function to do common things
#define standard_init() watchdog_disable(); enable_interrupts(); init_pins(); clock_init()

// Initial pin config
#define init_pins()     P1DIR = 0xFF; P1OUT = 0x00; \
                        P2DIR = 0xFF; P2OUT = 0x00; \
                        P3DIR = 0xFF; P3OUT = 0x00; \
                        P4DIR = 0xFF; P4OUT = 0x00; \
                        P5DIR = 0xFF; P5OUT = 0x00; \
                        P6DIR = 0xFF; P6OUT = 0x00; \
                        P7DIR = 0xFF; P7OUT = 0x00; \
                        P8DIR = 0xFF; P8OUT = 0x00


/**
 * Watchdog
 * TODO: watchdog_pet() directive to keep the watchdog timer going
 */
#define watchdog_disable()  WDTCTL = WDTPW + WDTHOLD



/**
 * Interrupts
 */
#define enable_interrupts()  __enable_interrupt();




/**
 * System Clock Initialization
 * Below is FLL magic, just take this for what it is and don't question it
 */
#define CRYSTAL_FREQ_KHZ  32768     // Frequency of the crystal used in kHz
#define MCLK_FREQ_HZ      20000000  // Default frequency in Hz

#define clock_init()    UCSCTL3 &= ~(0x0070);   /* Select XT1CLK (our onboard 32.768kHz crystal) as the FLL reference */ \
                        UCSCTL4 &= ~(0x0070);   /* Select XT1CLK as ACLK */ \
                        uint16_t ratio, dco_div_bits; \
                        uint8_t mode = 0; /* DC0CLK or DC0CLKDIV? */ \
                        uint16_t sysfreq = MCLK_FREQ_HZ / 1000; /* System frequency in kHz */ \
                        ratio = MCLK_FREQ_HZ / CRYSTAL_FREQ_KHZ; /* Ratio of system_freq -> FLL reference freq */ \
                        if (sysfreq > 16000) { ratio >>= 1; mode = 1; } /* Is sysfreq > 16Mhz? If so use DC0CLK rather than DC0CLKDIV */ \
                        else { sysfreq <<= 1; } \
                        while(ratio > 512) { dco_div_bits += FLLD0; ratio >>= 1; } \
                        __bis_SR_register(SCG0); /* Disable the FLL while we change the clocks */ \
                        UCSCTL0 = 0x0000; /* Set the DC0 to the lowest tap setting */ \
                        UCSCTL2 &= ~(0x3FF); /* Clear the 8 LSBs in the register to clear the FLLN bits */ \
                        UCSCTL2 = dco_div_bits | (ratio - 1); /* Datasheet voodoo */ \
                        if (sysfreq <= 630) UCSCTL1 = DCORSEL_0; \
                        else if (sysfreq < 1250) UCSCTL1 = DCORSEL_1; \
                        else if (sysfreq < 2500) UCSCTL1 = DCORSEL_2; \
                        else if (sysfreq < 5000) UCSCTL1 = DCORSEL_3; \
                        else if (sysfreq < 10000) UCSCTL1 = DCORSEL_4; \
                        else if (sysfreq < 20000) UCSCTL1 = DCORSEL_5; \
                        else if (sysfreq < 40000) UCSCTL1 = DCORSEL_6; \
                        else UCSCTL1 = DCORSEL_7; \
                        __bic_SR_register(SCG0); /* Re-enable the FLL */ \
                        if (mode == 1) { UCSCTL4 &= ~(0x0077); UCSCTL4 |= 0x0033; } \
                        else { UCSCTL4 &= ~(0x0077); UCSCTL4 |= 0x0044; } \
                        __delay_cycles(625000)

#endif

/**
 * Include the rest of the drivers
 * This will reduce the number of imports the user needs to add themselves
 */
#include "solarcar_spi.h"
#include "solarcar_can.h"
