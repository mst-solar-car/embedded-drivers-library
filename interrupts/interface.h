/**
 * This is the interface for the interrupt drivers
 *
 * Authors: Michael Rouse
 */
#ifndef __INTERRUPTS_INTERFACE__
#define __INTERRUPTS_INTERFACE__
#include "../library.h"


/* Enable/Disable interrupts */
#define interrupts_enable()     interrupts_set_state(Enable);
#define interrupts_disable()    interrupts_set_state(Disable);
void interrupts_set_state(bool enable);


/* Registers an event with on a pin */
void interrupt_attach(io_pin pin, void(*func)(void));


/* Dispatches an interrupt to the appropriate function if it exists */
void __interrupt_dispatch(uint8_t port);

/* Initialization, not ran by the user */
void interrupt_initialization(void(*mc_interrupt_set_state)(bool));



/* Shortcuts for creating interrupts */
#define interrupt_pin_ISR(pin)    void __##pin##_ISR(void);                                                      \
                                  void __attribute__((constructor)) __##pin##_INTERRUPT_ISR_CONSTRUCTOR (void) { \
                                    interrupt_attach(pin, __##pin##_ISR);                                         \
                                  };                                                                            \
                                  void __##pin##_ISR(void)
#define interrupt_ISR(vector)    void __attribute__((interrupt(vector))) __##vector##_ISR(void)



#endif