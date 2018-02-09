/**
 * Memory Utils
 *
 * Authors: Michael Rouse
 */
#ifndef __MEMORY_UTILS_INTERFACE__
#define __MEMORY_UTILS_INTERFACE__

#include "../../datatypes.h"

/* Simple Memory Copy */
void utils_memcpy(void* destination, void* source, uint16_t size);

#endif