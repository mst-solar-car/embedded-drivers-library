# Utility Drivers
This driver is actually composed up of a bunch of drivers that perform "utility" operations.

These drivers are here for the purpose of making code easier to write for whoever is writing
drivers, or whoever is programming a board.

&nbsp;

To use any, or all, of these utilities all you need to do is:
```c
#include "utils/interface.h"
```

&nbsp;

# Utilities
The following table gives a description to the utilities this driver includes, as well as a link to more info:

| Utility Driver | Description |
|----------------|-------------|
|[Bits](bits/README.md) | Helpeful bit/byte operations. |
|[Exception](exception/README.md)| Exceptions (`Try`/`Catch`) in pure C. |
|[Memory](memory/README.md) | Memory allocation and copying operations. |
|[PubSub](pubsub/README.md) | Publication and Subscription of events. |
|[Queue](queue/README.md) | A generic queue that can be used with any type. |