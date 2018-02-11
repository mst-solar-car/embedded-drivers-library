/**
 * Header file for directives that used for the inner workings of this library.
 * They can be used in user code, but they are mainly for making things easier
 * in the library.
 *
 * Authors: Michael Rouse
 */
#ifndef __INTERNALS__
#define __INTERNALS__

#include "datatypes.h"

typedef struct _pin_map_t {
  uint8_t port;
  uint8_t bit;
} pin_map_t;


/* Information about a Pin */
typedef struct _pin_info_t {
  uint8_t port;
  uint8_t bit;
  vuint8_t* dir_reg;
  vuint8_t* out_reg;
  vuint8_t* in_reg;
  vuint8_t* sel_reg;
  vuint8_t* ies_reg;
  vuint8_t* ie_reg;
  vuint8_t* ifg_reg;
} pin_info_t;


#define GetPinInfo(pin) ((pin > MC_NUMBER_OF_PINS || pin < 1) ? __NO_PIN_INFO :  \
  ((pin_info_t){                                                          \
    pin_map[pin].port,                                                    \
    pin_map[pin].bit,                                                     \
    (vuint8_t*)dir_registers[pin_map[pin].port],                          \
    (vuint8_t*)out_registers[pin_map[pin].port],                          \
    (vuint8_t*)in_registers[pin_map[pin].port],                           \
    (vuint8_t*)sel_registers[pin_map[pin].port],                          \
    (vuint8_t*)ies_registers[pin_map[pin].port],                          \
    (vuint8_t*)ie_registers[pin_map[pin].port],                           \
    (vuint8_t*)ifg_registers[pin_map[pin].port]                           \
  }))

#define IsValidPinInfo(pi)    (pi.port != NO_PORT && pi.bit != NO_BIT)

/* Pin Info for No Pin */
#define __NO_PIN_INFO               \
  ((pin_info_t) {                   \
    NO_PORT,                        \
    NO_BIT,                         \
    (vuint8_t*)NO_REGISTER,         \
    (vuint8_t*)NO_REGISTER,         \
    (vuint8_t*)NO_REGISTER,         \
    (vuint8_t*)NO_REGISTER,         \
    (vuint8_t*)NO_REGISTER,         \
    (vuint8_t*)NO_REGISTER,         \
    (vuint8_t*)NO_REGISTER,         \
  })


/* Information about a Port */
typedef struct _port_info_t {
  uint8_t port;
  vuint8_t* dir_reg;
  vuint8_t* out_reg;
  vuint8_t* in_reg;
  vuint8_t* sel_reg;
  vuint8_t* ies_reg;
  vuint8_t* ie_reg;
  vuint8_t* ifg_reg;
} port_info_t;


#define GetPortInfo(port) ((port > MC_NUMBER_OF_PORTS || port < 1) ? __NO_PORT_INFO :  \
  ((port_info_t){                                                               \
    port,                                                                       \
    (vuint8_t*)dir_registers[port],                                             \
    (vuint8_t*)out_registers[port],                                             \
    (vuint8_t*)in_registers[port],                                              \
    (vuint8_t*)sel_registers[port],                                             \
    (vuint8_t*)ies_registers[port],                                             \
    (vuint8_t*)ie_registers[port],                                              \
    (vuint8_t*)ifg_registers[port],                                             \
  }))

#define IsValidPortInfo(pi)   (pi.port != NO_PORT)

/* Info for an invalid Port */
#define __NO_PORT_INFO              \
  ((port_info_t) {                  \
    NO_PORT,                        \
    (vuint8_t*)NO_REGISTER,         \
    (vuint8_t*)NO_REGISTER,         \
    (vuint8_t*)NO_REGISTER,         \
    (vuint8_t*)NO_REGISTER,         \
    (vuint8_t*)NO_REGISTER,         \
    (vuint8_t*)NO_REGISTER,         \
    (vuint8_t*)NO_REGISTER,         \
  })




/**
 * Bit Helpers
 */
/* This will convert BIT0 -> 1, BIT4 -> 5, etc... (for indexing in an array) */
#define GetBitIndex(b)         \
  ((uint8_t)(                   \
    (b == BIT0) ? 1  :          \
    (b == BIT1) ? 2  :          \
    (b == BIT2) ? 3  :          \
    (b == BIT3) ? 4  :          \
    (b == BIT4) ? 5  :          \
    (b == BIT5) ? 6  :          \
    (b == BIT6) ? 7  :          \
    (b == BIT7) ? 8  :          \
    (b == BIT8) ? 9  :          \
    (b == BIT9) ? 10 :          \
    (b == BITA) ? 11 :          \
    (b == BITB) ? 12 :          \
    (b == BITC) ? 13 :          \
    (b == BITD) ? 14 :          \
    (b == BITE) ? 15 :          \
    (b == BITF) ? 16 :          \
    NO_BIT                      \
  ))

/* This does the opposite of GetBitIndex */
#define GetBitFromIndex(i)  \
  (                         \
    (i == 1)  ? BIT0 :      \
    (i == 2)  ? BIT1 :      \
    (i == 3)  ? BIT2 :      \
    (i == 4)  ? BIT3 :      \
    (i == 5)  ? BIT4 :      \
    (i == 6)  ? BIT5 :      \
    (i == 7)  ? BIT6 :      \
    (i == 8)  ? BIT7 :      \
    (i == 9)  ? BIT8 :      \
    (i == 10) ? BIT9 :      \
    (i == 11) ? BITA :      \
    (i == 12) ? BITB :      \
    (i == 13) ? BITC :      \
    (i == 14) ? BITD :      \
    (i == 15) ? BITE :      \
    (i == 16) ? BITF :      \
    NO_BIT                  \
  )





/* Allow access to these */
extern pin_map_t pin_map[];
extern vuint8_t* out_registers[];
extern vuint8_t* in_registers[];
extern vuint8_t* dir_registers[];
extern vuint8_t* sel_registers[];
extern vuint8_t* ies_registers[];
extern vuint8_t* ie_registers[];
extern vuint8_t* ifg_registers[];

#endif