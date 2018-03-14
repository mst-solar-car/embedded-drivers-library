# Queue Drivers
This queue driver is a generic queue that can be used with any data type.

&nbsp;

# Functions

| Syntax | Description |
|--------|-------------|
|`Queue_New(type)` | Creates a new Queue of `type`. |
|`Queue_Push(queue, data)` | Pushes `data` onto `queue` |
|`Queue_Pop(queue)` | Removes the next item in the `queue`, returns a null pointer if nothing is in the queue. |
|`Queue_Delete(queue)` | Cleans up memory allocations for the `queue`, use in unit tests. |

&nbsp;

# Constants

| Name | Value |
|------|-------|
|`QUEUE_SIZE` | `12` (`100` if Unit Testing). <br/>User can overwrite this.|

&nbsp;

# Types

| Name | Underlying Type |
|------|-----------------|
|`data_wrapper`| Struct: see [interface.h](interface.h) |
|`Queue` | Struct: see [interface.h](interface.h) |