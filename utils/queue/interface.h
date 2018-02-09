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

/* Use these directives to interact with the queue */
#define Queue_New(type)         __Queue_New(sizeof(type));
#define Queue_Push(queue, data) __Queue_Push(queue, data, sizeof(*data))
#define Queue_Pop(queue)        __Queue_Pop(queue) /* Just for consistency */
#define Queue_Delete(queue)     __Queue_Delete(&queue)















/* Actual function sunderlying those directives (You could call these directly, but why?) */
Queue*  __Queue_New(uint16_t datatype_size);
void*   __Queue_Pop(Queue* queue);
void    __Queue_Push(Queue* queue, void* data, uint16_t size);
void    __Queue_Delete(Queue** queue);



#endif