/**
 * Interface for a Circular Queue (Ring BUffer)
 *
 * Authors: Michael Rouse
 */
#ifndef __QUEUE_INTERFACE__
#define __QUEUE_INTERFACE__

#include "../../datatypes.h"


#ifndef QUEUE_SIZE
#define QUEUE_SIZE 32
#endif


/* Incomplete struct since this is a multiple instance module */
typedef struct Queue Queue;

/* Directives for a "Generic" Type */
#define Queue_New(type)         __Queue_New(sizeof(type*));
#define Queue_Push(queue, data) __Queue_Push(queue, (void*)data, sizeof(data))
#define Queue_Pop(queue)        __Queue_Pop(queue) /* Just for consistency */
#define Queue_Delete(queue)     free(queue)


/* Actual function sunderlying those directives */
Queue*  __Queue_New(uint16_t datatype_size);
void*   __Queue_Pop(Queue* queue);
void    __Queue_Push(Queue* queue, void* data, uint16_t size);




#endif