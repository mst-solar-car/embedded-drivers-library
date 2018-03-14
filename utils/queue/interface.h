/**
 * Interface for a Circular Queue (Ring BUffer)
 *
 * Authors: Michael Rouse
 */
#ifndef __QUEUE_INTERFACE__
#define __QUEUE_INTERFACE__

#include "../../datatypes.h"


/* Use these directives to interact with the queue */
#define Queue_New(type)         __Queue_New(sizeof(type));
#define Queue_Push(queue, data) __Queue_Push(queue, data, sizeof(*data))
#define Queue_Pop(queue)        __Queue_Pop(queue) /* Just for consistency */
#define Queue_Delete(queue)     __Queue_Delete(&queue)


/* Constants */
#ifndef QUEUE_SIZE
#define QUEUE_SIZE 32
#endif

#ifdef UNIT_TEST
#undef QUEUE_SIZE
#define QUEUE_SIZE  100
#endif

/* This struct will hold data for each item--most important thing is the read flag */
typedef struct data_wrapper_t {
  bool read;
  void* data;
} data_wrapper;

/* Incomplete struct since this is a multiple instance module */
typedef struct Queue {
  data_wrapper buffer[QUEUE_SIZE];
  uint8_t head;
  uint8_t tail;
} Queue;







/* Actual function sunderlying those directives (You could call these directly, but why?) */
Queue*  __Queue_New(uint16_t datatype_size);
void*   __Queue_Pop(Queue* queue);
void    __Queue_Push(Queue* queue, void* data, uint16_t size);
void    __Queue_Delete(Queue** queue);



#endif
