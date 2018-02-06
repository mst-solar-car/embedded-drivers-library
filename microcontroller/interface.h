/**
 * This file is the interface for all Microcontroller Drivers that may be implemented
 * in the future.
 *
 *
 * Authors: Michael Rouse
 */
#ifndef __MICROCONTROLLER_INTERFACE__
#define __MICROCONTROLLER_INTERFACE__



/* This function is for initializing the Microcontroller drivers, it should be */
/* implemented with every driver for each microcontroller. It should do basic generic */
/* initialization such as pins and clocks. */
/* It should NOT be called by the user. */
void microcontroller_initialization(void);





#endif