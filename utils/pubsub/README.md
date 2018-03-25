# PubSub Utility
The PubSub utility allows for publications of events that will trigger function calls (subscriptions) to occur.

These can be useful to do something when the internals of a driver are doing something.

&nbsp;

# Functions

| Syntax | Description |
|--------|-------------|
|`pubsub_event_id pubsub_new_event()` | Registers a new event, keep the return value of this. |
|`pubsub_publish(pubsub_event_id)` | Tells the driver that the event `pubsub_event_id` is happening and will trigger subcription callbacks. |
|`pubsub_subscribe(pubsub_event_id, func)` | Registers `func` to be called when `pubsub_event_id` is published. |

&nbsp;

# Constants

| Constant | Value |
|----------|-------|
|`PUBSUB_MAX_NUMBER_OF_EVENTS`| `20` |
|`PUBSUB_MAX_SUBSCRIBERS_PER_EVENT`| `5` |
|&nbsp;|&nbsp;|
|`PUBSUB_INVALID_ID` | `-1` |

&nbsp;

# Types

| Name | Underlying Type |
|------|-----------------|
|`pubsub_event_id` | `int8_t` |
|`pubsub_event` | Struct: see [interface.h](interface.h) |