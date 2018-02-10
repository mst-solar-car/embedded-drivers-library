/**
 * This file contains directives for a Fixture that makes creating microcontroller
 * drivers easier and simpler to read. A Fixture is just a wrapper.
 *
 * Authors: Michael Rouse
 */
#include "interface.h"
#include "../datatypes.h"




/**
 * Ports and Pins
 */
#ifdef RUN_SPEC_FILE_LIKE_C_FILE
#undef REGISTER_PINS
#define REGISTER_PINS(numberOfPins) pin_map_t pin_map[numberOfPins];
#else
#undef REGISTER_PINS
#define REGISTER_PINS(numberOfPins) enum { \
                                      _C(_LIST_PINS_, numberOfPins)() \
                                    };
#endif

#ifdef RUN_SPEC_FILE_LIKE_C_FILE
#undef REGISTER_PORTS
#define REGISTER_PORTS(...) vuint16_t* dir_registers[NUM_ARGS(__VA_ARGS__)]; \
                            vuint16_t* out_registers[NUM_ARGS(__VA_ARGS__)]; \
                            vuint16_t* in_registers[NUM_ARGS(__VA_ARGS__)]; \
                            vuint16_t* sel_registers[NUM_ARGS(__VA_ARGS__)]; \
                            vuint16_t* ies_registers[NUM_ARGS(__VA_ARGS__)]; \
                            vuint16_t* ie_registers[NUM_ARGS(__VA_ARGS__)]; \
                            vuint16_t* ifg_registers[NUM_ARGS(__VA_ARGS__)];
#else
#undef REGISTER_PORTS
#define REGISTER_PORTS(...) enum { \
                              _C(_LIST_PORTS_, NUM_ARGS(__VA_ARGS__))(__VA_ARGS__) \
                            };
#endif

/* Set port bits to pins in bulk */
#ifdef RUN_SPEC_FILE_LIKE_C_FILE
#undef REGISTER_PINS_FOR_PORT
#define REGISTER_PINS_FOR_PORT(port, ...)   void __attribute__((constructor)) __PORT##port##_SETUP(void) { \
                                              _C(_SETUP_PIN_MAP_, NUM_ARGS(__VA_ARGS__))(port, __VA_ARGS__) \
                                            };
#else
#undef REGISTER_PINS_FOR_PORT
#define REGISTER_PINS_FOR_PORT(port, ...)   enum { \
                                              _C(_PORT_BITS_, NUM_ARGS(__VA_ARGS__))(port, __VA_ARGS__) \
                                            };
#endif

/* Set individually */
#ifdef RUN_SPEC_FILE_LIKE_C_FILE
#undef REGISTER_PIN_FOR_PORT_BIT
#define REGISTER_PIN_FOR_PORT_BIT(port, bit, pin)   void __attribute__((constructor)) __PORT##port##_B##bit##_SETUP(void) { \
                                                      pin_map[pin].port = port; \
                                                      pin_map[pin].bit = bit; \
                                                    }
#else
#undef REGISTER_PIN_FOR_PORT_BIT
#define REGISTER_PIN_FOR_PORT_BIT(port, bit, pin)   enum { \
                                                      PORTB_NAME(port, bit) = pin, \
                                                    };
#endif

/* Add ability to register pin aliases (other functions, etc..) */
#ifdef RUN_SPEC_FILE_LIKE_C_FILE
#undef REGISTER_PIN_ALIAS
#define REGISTER_PIN_ALIAS(alias, pin)
#else
#undef REGISTER_PIN_ALIAS
#define REGISTER_PIN_ALIAS(alias, pin)  enum { \
                                          alias = pin, \
                                        };
#endif

/* Setup Registers for the Ports */
#ifdef RUN_SPEC_FILE_LIKE_C_FILE
#undef SET_PORT_REGISTERS
#define SET_PORT_REGISTERS(port, dir, out, in, sel, ies, ie, ifg)  \
                                      void __attribute__((constructor)) PORT##port##_REGISTER_SETUP(void) { \
                                        dir_registers[PORT_NAME(port)] = REG(dir); \
                                        out_registers[PORT_NAME(port)] = REG(out); \
                                        in_registers[PORT_NAME(port)] = REG(in); \
                                        sel_registers[PORT_NAME(port)] = REG(sel); \
                                        ies_registers[PORT_NAME(port)] = REG(ies); \
                                        ie_registers[PORT_NAME(port)] = REG(ie); \
                                        ifg_registers[PORT_NAME(port)] = REG(ifg); \
                                      }
#else
#undef SET_PORT_REGISTERS
#define SET_PORT_REGISTERS(port, dir, out, in, sel, ies, ie, ifg)
#endif


/**
 * Interrupts
 */
#ifdef RUN_SPEC_FILE_LIKE_C_FILE
#undef REGISTER_NONPIN_INTERRUPT
#define REGISTER_NONPIN_INTERRUPT(vector, ...)  void __attribute__((interrupt(vector))) __##vector##_ISR(void)\
                                                { \
                                                  { \
                                                    __VA_ARGS__ \
                                                  } \
                                                };
#else
#undef REGISTER_NONPIN_INTERRUPT
#define REGISTER_NONPIN_INTERRUPT(vector, ...)
#endif

#ifdef RUN_SPEC_FILE_LIKE_C_FILE
#undef REGISTER_PIN_INTERRUPT
#define REGISTER_PIN_INTERRUPT(vector, port)    REGISTER_NONPIN_INTERRUPT(vector, { \
                                                });
#else
#undef REGISTER_PIN_INTERRUPT
#define REGISTER_PIN_INTERRUPT(vector, port)
#endif


/**
 * Helper Directives
 * (Nitty and Gritty)
 */
#ifndef __MICROCONTROLLER_FIXTURE__
#define __MICROCONTROLLER_FIXTURE__

/* Register Creation */
#define REG(name) (vuint16_t*)name

#define PIN_NAME(n)       PIN##n
#define PORTB_NAME(n, b)  P##n##_##b
#define PORT_NAME(n)      PORT##n

#define _C(a, ...)	_PRIMITIVE_CAT(a, __VA_ARGS__)
#define _PRIMITIVE_CAT(a, ...) 	a ## __VA_ARGS__
#ifndef _NUM_ARGS
#define _NUM_ARGS(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, Pn, ...) Pn
#endif
#ifndef NUM_ARGS
#define NUM_ARGS(...) _NUM_ARGS(-1, ##__VA_ARGS__, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#endif



/**
 * You might not want to look below this line :)
 */



































/**
 * Aaaaaaye, you made it. That sucks.
 * If you made it this far then something must be broken or you are curious.
 *
 * If something is broken--I'm sorry.
 * If you're curious--I'm still sorry.
 */
#define _LIST_PORT(p)                                                 PORT_NAME(p),
#define _LIST_PORTS_0()                                               NYIASFLASF,
#define _LIST_PORTS_1(p1)                                             _LIST_PORTS_0() _LIST_PORT(p1)
#define _LIST_PORTS_2(p1, p2)                                         _LIST_PORTS_1(p1) _LIST_PORT(p2)
#define _LIST_PORTS_3(p1, p2, p3)                                     _LIST_PORTS_2(p1, p2) _LIST_PORT(p3)
#define _LIST_PORTS_4(p1, p2, p3, p4)                                 _LIST_PORTS_3(p1, p2, p3) _LIST_PORT(p4)
#define _LIST_PORTS_5(p1, p2, p3, p4, p5)                             _LIST_PORTS_4(p1, p2, p3, p4) _LIST_PORT(p5)
#define _LIST_PORTS_6(p1, p2, p3, p4, p5, p6)                         _LIST_PORTS_5(p1, p2, p3, p4, p5) _LIST_PORT(p6)
#define _LIST_PORTS_7(p1, p2, p3, p4, p5, p6, p7)                     _LIST_PORTS_6(p1, p2, p3, p4, p5, p6) _LIST_PORT(p7)
#define _LIST_PORTS_8(p1, p2, p3, p4, p5, p6, p7, p8)                 _LIST_PORTS_7(p1, p2, p3, p4, p5, p6, p7) _LIST_PORT(p8)
#define _LIST_PORTS_9(p1, p2, p3, p4, p5, p6, p7, p8, p9)             _LIST_PORTS_8(p1, p2, p3, p4, p5, p6, p7, p8) _LIST_PORT(p9)
#define _LIST_PORTS_10(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)       _LIST_PORTS_9(p1, p2, p3, p4, p5, p6, p7, p8, p9) _LIST_PORT(p10)
#define _LIST_PORTS_11(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11)  _LIST_PORTS_10(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10) _LIST_PORT(p11)


#define BTP(n,b,p)                                  PORTB_NAME(n,b) = PIN_NAME(p),
#define _PORT_BITS_1(n, p1)                         BTP(n,0,p1)
#define _PORT_BITS_2(n, p1, p2)                     _PORT_BITS_1(n, p1) BTP(n,1,p2)
#define _PORT_BITS_3(n, p1, p2, p3)                 _PORT_BITS_2(n, p1, p2) BTP(n,2,p3)
#define _PORT_BITS_4(n, p1, p2, p3, p4)             _PORT_BITS_3(n,p1,p2,p3) BTP(n,3,p4)
#define _PORT_BITS_5(n,p1,p2,p3,p4,p5)              _PORT_BITS_4(n,p1,p2,p3,p4) BTP(n,4,p5)
#define _PORT_BITS_6(n,p1,p2,p3,p4,p5,p6)           _PORT_BITS_5(n,p1,p2,p3,p4,p5) BTP(n,5,p6)
#define _PORT_BITS_7(n,p1,p2,p3,p4,p5,p6,p7)        _PORT_BITS_6(n,p1,p2,p3,p4,p5,p6) BTP(n,6,p7)
#define _PORT_BITS_8(n,p1,p2,p3,p4,p5,p6,p7,p8)     _PORT_BITS_7(n,p1,p2,p3,p4,p5,p6,p7) BTP(n,7,p8)
#define _PORT_BITS_9(n,p1,p2,p3,p4,p5,p6,p7,p8,p9)  _PORT_BITS_8(n,p1,p2,p3,p4,p5,p6,p7,p8) BTP(n,8,p9)


#define _SETUP_PIN_MAP(n,b,p)                           pin_map[p].port = PORT_NAME(n); pin_map[p].bit = b;
#define _SETUP_PIN_MAP_1(n,p1)                          _SETUP_PIN_MAP(n,1,p1)
#define _SETUP_PIN_MAP_2(n,p1,p2)                       _SETUP_PIN_MAP_1(n,p1) _SETUP_PIN_MAP(n,2,p2)
#define _SETUP_PIN_MAP_3(n,p1,p2,p3)                    _SETUP_PIN_MAP_2(n,p1,p2) _SETUP_PIN_MAP(n,3,p3)
#define _SETUP_PIN_MAP_4(n,p1,p2,p3,p4)                 _SETUP_PIN_MAP_3(n,p1,p2,p3) _SETUP_PIN_MAP(n,4,p4)
#define _SETUP_PIN_MAP_5(n,p1,p2,p3,p4,p5)              _SETUP_PIN_MAP_4(n,p1,p2,p3,p4) _SETUP_PIN_MAP(n,5,p5)
#define _SETUP_PIN_MAP_6(n,p1,p2,p3,p4,p5,p6)           _SETUP_PIN_MAP_5(n,p1,p2,p3,p4,p5) _SETUP_PIN_MAP(n,6,p6)
#define _SETUP_PIN_MAP_7(n,p1,p2,p3,p4,p5,p6,p7)        _SETUP_PIN_MAP_6(n,p1,p2,p3,p4,p5,p6) _SETUP_PIN_MAP(n,7,p7)
#define _SETUP_PIN_MAP_8(n,p1,p2,p3,p4,p5,p6,p7,p8)     _SETUP_PIN_MAP_7(n,p1,p2,p3,p4,p5,p6,p7) _SETUP_PIN_MAP(n,8,p8)
#define _SETUP_PIN_MAP_9(n,p1,p2,p3,p4,p5,p6,p7,p8,p9)  _SETUP_PIN_MAP_8(n,p1,p2,p3,p4,p5,p6,p7,p8) _SETUP_PIN_MAP(n,9,p9)



#define _LIST_PIN(n)    PIN_NAME(n) = n,
#define _LIST_PINS_1()  _LIST_PIN(1)
#define _LIST_PINS_2()  _LIST_PINS_1()  _LIST_PIN(2)
#define _LIST_PINS_3()  _LIST_PINS_2()  _LIST_PIN(3)
#define _LIST_PINS_4()  _LIST_PINS_3()  _LIST_PIN(4)
#define _LIST_PINS_5()  _LIST_PINS_4()  _LIST_PIN(5)
#define _LIST_PINS_6()  _LIST_PINS_5()  _LIST_PIN(6)
#define _LIST_PINS_7()  _LIST_PINS_6()  _LIST_PIN(7)
#define _LIST_PINS_8()  _LIST_PINS_7()  _LIST_PIN(8)
#define _LIST_PINS_9()  _LIST_PINS_8()  _LIST_PIN(9)
#define _LIST_PINS_10() _LIST_PINS_9()  _LIST_PIN(10)
#define _LIST_PINS_11() _LIST_PINS_10() _LIST_PIN(11)
#define _LIST_PINS_12() _LIST_PINS_11() _LIST_PIN(12)
#define _LIST_PINS_13() _LIST_PINS_12() _LIST_PIN(13)
#define _LIST_PINS_14() _LIST_PINS_13() _LIST_PIN(14)
#define _LIST_PINS_15() _LIST_PINS_14() _LIST_PIN(16)
#define _LIST_PINS_16() _LIST_PINS_15() _LIST_PIN(15)
#define _LIST_PINS_17() _LIST_PINS_16() _LIST_PIN(18)
#define _LIST_PINS_18() _LIST_PINS_17() _LIST_PIN(17)
#define _LIST_PINS_19() _LIST_PINS_18() _LIST_PIN(19)
#define _LIST_PINS_20() _LIST_PINS_19() _LIST_PIN(20)
#define _LIST_PINS_21() _LIST_PINS_20() _LIST_PIN(22)
#define _LIST_PINS_22() _LIST_PINS_21() _LIST_PIN(21)
#define _LIST_PINS_23() _LIST_PINS_22() _LIST_PIN(23)
#define _LIST_PINS_24() _LIST_PINS_23() _LIST_PIN(24)
#define _LIST_PINS_25() _LIST_PINS_24() _LIST_PIN(25)
#define _LIST_PINS_26() _LIST_PINS_25() _LIST_PIN(26)
#define _LIST_PINS_27() _LIST_PINS_26() _LIST_PIN(28)
#define _LIST_PINS_28() _LIST_PINS_27() _LIST_PIN(27)
#define _LIST_PINS_29() _LIST_PINS_28() _LIST_PIN(29)
#define _LIST_PINS_30() _LIST_PINS_29() _LIST_PIN(30)
#define _LIST_PINS_31() _LIST_PINS_30() _LIST_PIN(31)
#define _LIST_PINS_32() _LIST_PINS_31() _LIST_PIN(32)
#define _LIST_PINS_33() _LIST_PINS_32() _LIST_PIN(33)
#define _LIST_PINS_34() _LIST_PINS_33() _LIST_PIN(34)
#define _LIST_PINS_35() _LIST_PINS_34() _LIST_PIN(36)
#define _LIST_PINS_36() _LIST_PINS_35() _LIST_PIN(35)
#define _LIST_PINS_37() _LIST_PINS_36() _LIST_PIN(37)
#define _LIST_PINS_38() _LIST_PINS_37() _LIST_PIN(38)
#define _LIST_PINS_39() _LIST_PINS_38() _LIST_PIN(39)
#define _LIST_PINS_40() _LIST_PINS_39() _LIST_PIN(40)
#define _LIST_PINS_41() _LIST_PINS_40() _LIST_PIN(41)
#define _LIST_PINS_42() _LIST_PINS_41() _LIST_PIN(42)
#define _LIST_PINS_43() _LIST_PINS_42() _LIST_PIN(43)
#define _LIST_PINS_44() _LIST_PINS_43() _LIST_PIN(44)
#define _LIST_PINS_45() _LIST_PINS_44() _LIST_PIN(45)
#define _LIST_PINS_46() _LIST_PINS_45() _LIST_PIN(46)
#define _LIST_PINS_47() _LIST_PINS_46() _LIST_PIN(47)
#define _LIST_PINS_48() _LIST_PINS_47() _LIST_PIN(48)
#define _LIST_PINS_49() _LIST_PINS_48() _LIST_PIN(50)
#define _LIST_PINS_50() _LIST_PINS_49() _LIST_PIN(49)
#define _LIST_PINS_51() _LIST_PINS_50() _LIST_PIN(51)
#define _LIST_PINS_52() _LIST_PINS_51() _LIST_PIN(52)
#define _LIST_PINS_53() _LIST_PINS_52() _LIST_PIN(53)
#define _LIST_PINS_54() _LIST_PINS_53() _LIST_PIN(54)
#define _LIST_PINS_55() _LIST_PINS_54() _LIST_PIN(55)
#define _LIST_PINS_56() _LIST_PINS_55() _LIST_PIN(56)
#define _LIST_PINS_57() _LIST_PINS_56() _LIST_PIN(57)
#define _LIST_PINS_58() _LIST_PINS_57() _LIST_PIN(58)
#define _LIST_PINS_59() _LIST_PINS_58() _LIST_PIN(59)
#define _LIST_PINS_60() _LIST_PINS_59() _LIST_PIN(60)
#define _LIST_PINS_61() _LIST_PINS_60() _LIST_PIN(61)
#define _LIST_PINS_62() _LIST_PINS_61() _LIST_PIN(62)
#define _LIST_PINS_63() _LIST_PINS_62() _LIST_PIN(63)
#define _LIST_PINS_64() _LIST_PINS_63() _LIST_PIN(65)
#define _LIST_PINS_65() _LIST_PINS_64() _LIST_PIN(64)
#define _LIST_PINS_66() _LIST_PINS_65() _LIST_PIN(67)
#define _LIST_PINS_67() _LIST_PINS_66() _LIST_PIN(66)
#define _LIST_PINS_68() _LIST_PINS_67() _LIST_PIN(68)
#define _LIST_PINS_69() _LIST_PINS_68() _LIST_PIN(69)
#define _LIST_PINS_70() _LIST_PINS_69() _LIST_PIN(71)
#define _LIST_PINS_71() _LIST_PINS_70() _LIST_PIN(70)
#define _LIST_PINS_72() _LIST_PINS_71() _LIST_PIN(72)
#define _LIST_PINS_73() _LIST_PINS_72() _LIST_PIN(73)
#define _LIST_PINS_74() _LIST_PINS_73() _LIST_PIN(74)
#define _LIST_PINS_75() _LIST_PINS_74() _LIST_PIN(75)
#define _LIST_PINS_76() _LIST_PINS_75() _LIST_PIN(77)
#define _LIST_PINS_77() _LIST_PINS_76() _LIST_PIN(76)
#define _LIST_PINS_78() _LIST_PINS_77() _LIST_PIN(78)
#define _LIST_PINS_79() _LIST_PINS_78() _LIST_PIN(79)
#define _LIST_PINS_80() _LIST_PINS_79() _LIST_PIN(80)
#define _LIST_PINS_81() _LIST_PINS_80() _LIST_PIN(81)
#define _LIST_PINS_82() _LIST_PINS_81() _LIST_PIN(82)
#define _LIST_PINS_83() _LIST_PINS_82() _LIST_PIN(83)
#define _LIST_PINS_84() _LIST_PINS_83() _LIST_PIN(85)
#define _LIST_PINS_85() _LIST_PINS_84() _LIST_PIN(84)
#define _LIST_PINS_86() _LIST_PINS_85() _LIST_PIN(86)
#define _LIST_PINS_87() _LIST_PINS_86() _LIST_PIN(87)
#define _LIST_PINS_88() _LIST_PINS_87() _LIST_PIN(88)
#define _LIST_PINS_89() _LIST_PINS_88() _LIST_PIN(89)
#define _LIST_PINS_90() _LIST_PINS_89() _LIST_PIN(90)
#define _LIST_PINS_91() _LIST_PINS_90() _LIST_PIN(91)
#define _LIST_PINS_92() _LIST_PINS_91() _LIST_PIN(92)
#define _LIST_PINS_93() _LIST_PINS_92() _LIST_PIN(93)
#define _LIST_PINS_94() _LIST_PINS_93() _LIST_PIN(94)
#define _LIST_PINS_95() _LIST_PINS_94() _LIST_PIN(95)
#define _LIST_PINS_96() _LIST_PINS_95() _LIST_PIN(96)
#define _LIST_PINS_97() _LIST_PINS_96() _LIST_PIN(97)
#define _LIST_PINS_98() _LIST_PINS_97() _LIST_PIN(98)
#define _LIST_PINS_99() _LIST_PINS_98() _LIST_PIN(99)
#define _LIST_PINS_100() _LIST_PINS_99() _LIST_PIN(100)

/* If you have over 100 pins then good luck */




#endif


/**
 * This is still apart of the same fixture, I just wanted it logically separated out
 */
#ifndef __MICROCONTROLLER_FIXTURE2__
#define __MICROCONTROLLER_FIXTURE2__






#endif