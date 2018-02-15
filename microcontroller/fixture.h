/**
 * This file contains directives for a Fixture that makes creating microcontroller
 * drivers easier and simpler to read. A Fixture is just a wrapper.
 *
 * So this file is weird. This fixture allows for the .spec file and the .driver
 * file to do what they do.
 *
 * For the .spec file, you might notice a lot of #ifdef RUN_SPEC_FILE_LIKE_C_FILE
 * directives in here, a lot of similar directives, and a lot of #undef
 * This is because this fixture forces the .spec file to behave differently whether it
 * is #include in a header file or a code file... :)
 * So sorry.
 *
 * Authors: Michael Rouse and people on the internet
 */
#include "interface.h"
#include "../datatypes.h"



/**
 * Ports and Pins
 */

/* Create list of pins */
#undef REGISTER_PINS
#undef _REGISTER_PIN
#ifdef RUN_SPEC_FILE_LIKE_C_FILE
  /* C File */
  #define REGISTER_PINS(numberOfPins)   pin_map_t pin_map[numberOfPins+1];

#else
  /* Header File */
  #define REGISTER_PINS(numberOfPins)                       \
    enum {                                                  \
      EVAL256(MAP_COUNTING(_REGISTER_PIN, numberOfPins))    \
      MC_NUMBER_OF_PINS = numberOfPins,                     \
    };

  #define _REGISTER_PIN(n)    PIN_NAME(n) = n,
#endif


/* Create list of ports */
#undef REGISTER_PORTS
#undef _REGISTER_PORT
#ifdef RUN_SPEC_FILE_LIKE_C_FILE
  /* C File */
  #define REGISTER_PORTS(...)                             \
    port_info_t port_map[NUM_ARGS(1, __VA_ARGS__)];

#else
  /* Header File */
  #define REGISTER_PORTS(...)                             \
    enum {                                                \
      __IGNORE_THIS_##__LINE__ = 0,                       \
      EVAL256(MAP(_REGISTER_PORT, __VA_ARGS__))           \
      MC_NUMBER_OF_PORTS = NUM_ARGS(__VA_ARGS__),         \
    };

  #define _REGISTER_PORT(p)    PORT_NAME(p),
#endif


/* Set port bits to pins in bulk */
#undef REGISTER_PINS_FOR_PORT
#ifdef RUN_SPEC_FILE_LIKE_C_FILE
  /* C File */
  #define REGISTER_PINS_FOR_PORT(port, ...)                             \
    void __attribute__((constructor(800))) __PORT##port##_SETUP(void) {      \
      CAT(_SETUP_PIN_MAP_, NUM_ARGS(__VA_ARGS__))(port, __VA_ARGS__)    \
    };

#else
  /* Header File */
  #define REGISTER_PINS_FOR_PORT(port, ...)                                   \
    enum {                                                                    \
      EVAL256(CAT(_PORT_BITS_, NUM_ARGS(__VA_ARGS__))(port, __VA_ARGS__))     \
      MC_NUMBER_OF_BITS_ON_PORT##port = NUM_ARGS(__VA_ARGS__),               \
    };
#endif


/* Register Pin Aliases (other functions, etc..) */
#undef REGISTER_PIN_ALIAS
#ifdef RUN_SPEC_FILE_LIKE_C_FILE
  /* C File */
  #define REGISTER_PIN_ALIAS(pin, alias)  /* Nothing */

#else
  /* Header File */
  #define REGISTER_PIN_ALIAS(pin, alias)      \
    enum {                                    \
      alias = pin,                            \
    };
#endif

/* Setup Registers for the Ports */
#undef SET_PORT_REGISTERS
#ifdef RUN_SPEC_FILE_LIKE_C_FILE
  /* C File */
  #define SET_PORT_REGISTERS(port, dir, out, in, sel, ies, ie, ifg)           \
    void __attribute__((constructor(300))) __PORT##port##_REGISTER_SETUP(void) {   \
      port_map[PORT_NAME(port)].number = PORT_NAME(port);                         \
      port_map[PORT_NAME(port)].dir_reg = REG(dir);                                \
      port_map[PORT_NAME(port)].out_reg = REG(out);                                 \
      port_map[PORT_NAME(port)].in_reg = REG(in);  \
      port_map[PORT_NAME(port)].sel_reg = REG(sel); \
      port_map[PORT_NAME(port)].ies_reg = REG(ies); \
      port_map[PORT_NAME(port)].ie_reg = REG(ie); \
      port_map[PORT_NAME(port)].ifg_reg = REG(ifg); \
    };

#else
  /* Header File */
  #define SET_PORT_REGISTERS(port, dir, out, in, sel, ies, ie, ifg) /* Nothing */
#endif


/**
 * SPI Buses
 */
#undef REGISTER_SPI_BUSES
#undef _REGISTER_SPI_BUS
#ifdef RUN_SPEC_FILE_LIKE_C_FILE
  /* C File */
  #define REGISTER_SPI_BUSES(n)  /* Nothing */

#else
  /* Header File */
  #define REGISTER_SPI_BUSES(n)                     \
    enum {                                          \
      EVAL256(MAP_COUNTING(_REGISTER_SPI_BUS, n))   \
      MC_NUMBER_OF_SPI_BUSES = n,                   \
    };

  #define _REGISTER_SPI_BUS(n)    SPI_BUS_##n = n,
#endif


/**
 * Interrupts
 */
#undef REGISTER_INTERRUPTABLE_PORTS
#undef _REGISTER_INTERRUPTABLE_PORT
#ifdef RUN_SPEC_FILE_LIKE_C_FILE
  /* C File */
  #define REGISTER_INTERRUPTABLE_PORTS(...)   EVAL256(MAP_PAIR_PARAMETERS(_REGISTER_INTERRUPTABLE_PORT, __VA_ARGS__))

  #define _REGISTER_INTERRUPTABLE_PORT(p,v)                           \
    void __attribute__((interrupt(v))) __##p##_ISR(void) {            \
      __interrupt_dispatch(p);                           \
    };

#else
  /* Header File */
  #define REGISTER_INTERRUPTABLE_PORTS(...)                         \
    enum {                                                          \
      MC_NUMBER_OF_INTERRUPTABLE_PORTS = NUM_ARGS(__VA_ARGS__),     \
    };
#endif


/**
 * System
 */
#undef CLOCK_SPEED_HZ
#ifdef RUN_SPEC_FILE_LIKE_C_FILE
  /* C File */
  #define CLOCK_SPEED_HZ(...)    /* Nothing */

#else
  /* Header File */
  #define CLOCK_SPEED_HZ(speed)                             \
    enum {                                                  \
      MC_CLOCK_SPEED_HZ = speed,                            \
    };
#endif



/**
 * Helper Directives
 * (Nitty and Gritty)
 */
#ifndef __MICROCONTROLLER_FIXTURE__
#define __MICROCONTROLLER_FIXTURE__

#define REG(name)         (vuint8_t*)name

#define PIN(n)            PIN##n
#define PIN_NAME(n)       PIN##n

#define PB(n, b)          P##n##_##b
#define PORTB_NAME(n, b)  P##n##_##b

#define PORT(n)           PORT##n
#define PORT_NAME(n)      PORT##n








/**
 * Aaaaaaye, you made it. That sucks.
 * If you made it this far then something must be broken or you are curious.
 *
 * If something is broken--I'm sorry.
 * If you're curious--I'm still sorry.
 */
#define BTP(n,b,p)                                        PORTB_NAME(n,b) = p,
#define _PORT_BITS_1(n, p1)                               BTP(n,0,p1)
#define _PORT_BITS_2(n, p1, p2)                           _PORT_BITS_1(n, p1) BTP(n,1,p2)
#define _PORT_BITS_3(n, p1, p2, p3)                       _PORT_BITS_2(n, p1, p2) BTP(n,2,p3)
#define _PORT_BITS_4(n, p1, p2, p3, p4)                   _PORT_BITS_3(n,p1,p2,p3) BTP(n,3,p4)
#define _PORT_BITS_5(n,p1,p2,p3,p4,p5)                    _PORT_BITS_4(n,p1,p2,p3,p4) BTP(n,4,p5)
#define _PORT_BITS_6(n,p1,p2,p3,p4,p5,p6)                 _PORT_BITS_5(n,p1,p2,p3,p4,p5) BTP(n,5,p6)
#define _PORT_BITS_7(n,p1,p2,p3,p4,p5,p6,p7)              _PORT_BITS_6(n,p1,p2,p3,p4,p5,p6) BTP(n,6,p7)
#define _PORT_BITS_8(n,p1,p2,p3,p4,p5,p6,p7,p8)           _PORT_BITS_7(n,p1,p2,p3,p4,p5,p6,p7) BTP(n,7,p8)
#define _PORT_BITS_9(n,p1,p2,p3,p4,p5,p6,p7,p8,p9)        _PORT_BITS_8(n,p1,p2,p3,p4,p5,p6,p7,p8) BTP(n,8,p9)


#define _SETUP_PIN_MAP(n,b,p)                             pin_map[p].port = PORT_NAME(n); pin_map[p].bit = BIT##b;
#define _SETUP_PIN_MAP_1(n,p1)                            _SETUP_PIN_MAP(n,0,p1)
#define _SETUP_PIN_MAP_2(n,p1,p2)                         _SETUP_PIN_MAP_1(n,p1) _SETUP_PIN_MAP(n,1,p2)
#define _SETUP_PIN_MAP_3(n,p1,p2,p3)                      _SETUP_PIN_MAP_2(n,p1,p2) _SETUP_PIN_MAP(n,2,p3)
#define _SETUP_PIN_MAP_4(n,p1,p2,p3,p4)                   _SETUP_PIN_MAP_3(n,p1,p2,p3) _SETUP_PIN_MAP(n,3,p4)
#define _SETUP_PIN_MAP_5(n,p1,p2,p3,p4,p5)                _SETUP_PIN_MAP_4(n,p1,p2,p3,p4) _SETUP_PIN_MAP(n,4,p5)
#define _SETUP_PIN_MAP_6(n,p1,p2,p3,p4,p5,p6)             _SETUP_PIN_MAP_5(n,p1,p2,p3,p4,p5) _SETUP_PIN_MAP(n,5,p6)
#define _SETUP_PIN_MAP_7(n,p1,p2,p3,p4,p5,p6,p7)          _SETUP_PIN_MAP_6(n,p1,p2,p3,p4,p5,p6) _SETUP_PIN_MAP(n,6,p7)
#define _SETUP_PIN_MAP_8(n,p1,p2,p3,p4,p5,p6,p7,p8)       _SETUP_PIN_MAP_7(n,p1,p2,p3,p4,p5,p6,p7) _SETUP_PIN_MAP(n,7,p8)
#define _SETUP_PIN_MAP_9(n,p1,p2,p3,p4,p5,p6,p7,p8,p9)    _SETUP_PIN_MAP_8(n,p1,p2,p3,p4,p5,p6,p7,p8) _SETUP_PIN_MAP(n,8,p9)






#endif




