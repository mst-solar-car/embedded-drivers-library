/**
 * PubSub allows for listening to certain events inside of a driver
 *
 * Authors: Michael Rouse
 */
#ifndef __PUBSUB_INTERFACE__
#define __PUBSUB_INTERFACE__
#ifndef PUBSUB_DISABLE // Ability to disable pubsub

#include "../../datatypes.h"


/* Configuration Constants */
enum {
  PUBSUB_MAX_NUMBER_OF_EVENTS = 20,
  PUBSUB_MAX_SUBSCRIBERS_PER_EVENT = 5
};
#define PUBSUB_INVALID_ID    -1

typedef int8_t pubsub_event_id;


typedef struct pubsub_event_t {
  voidFuncPtr subscribers[PUBSUB_MAX_SUBSCRIBERS_PER_EVENT];
  uint8_t _next_subscriber_index;
} pubsub_event;



/**
 * Interface Functions
 */

// Receive a new pubsub event id
pubsub_event_id pubsub_new_event();

// Publish an event to subscribers
void pubsub_publish(pubsub_event_id id);

// Subscribe to an event (similar to interrupt)
void pubsub_subscribe(pubsub_event_id id, void(*event_fn)(void));













#else
  // Dummy functions
  #define pubsub_new_event()              /* Nothing */
  #define pubsub_publish(event_id)        /* Nothing */
  #define pubsubs_subscribe(event_id, fn) /* Nothing */
#endif

#endif