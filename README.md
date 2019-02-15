# Embedded Drivers Library
This library contains drivers most commonly used for boards on the Solar Car Team.

Drivers are split up and *somewhat* independent of one-another. There are dependencies to the Utils drivers. All other dependencies are managed through the use of [function pointers](http://ernstsson.net/post/26821666317/dependency-inversion-in-c-using-function-pointers) to invert dependencies.

**Any functions that begin with a double underscrore `__function_name` should not be called by the user in production code!**

The table below provides a brief description of each driver and has a link to a more detailed README for those drivers.

| Driver | Description |
|--------|-------------|
| [CAN](can/README.md) | Generic CAN Drivers for receiving from and sending messages to a CAN Controller |
| [CAN Controller](can_controller/README.md) | Device-specific driver implementations of a generic CAN Controller interface (used by the CAN library) |
| [Interrupts](interrupts/README.md) | Generic driver for handling and dispatching interrupts on specific pins for any microcontroller |
| [Microcontroller](microcontroller/README.md) | Device-specific drivers for a microcontroller |
| [Pin Control](pin_control/README.md) | Generic driver for control pins on a microcontroller |
| [SPI](spi/README.md) | Generic SPI sending and receiving |
| [Testing](testing/README.md) | Unit Testing Framework |
| [Utils](utils/README.md) | Awesome utilities that you can use in drivers, or your code. <br/>(Exceptions, bit manipulation, memory, queues, etc...) |
| &nbsp; | &nbsp; |
| [Examples](EXAMPLES.md) | Crazy-good examples to show you how to do anything in this library!! <br/>If something you want to know about is not in here, try taking a look at the `.test` file for that driver! |
|&nbsp;|&nbsp;|
|[Unit Testing](TESTING.md)| Learn about running and writing Unit Tests for this library and your code that uses this library |

&nbsp;

# How To Use
If you're writing software for a board, you should definitely be using this driver library since it has Unit Tests to verify that it is fully functional.

This driver library is designed to be used as a [Git Submodule](https://git-scm.com/book/en/v2/Git-Tools-Submodules) so it can be updated on all projects really easily. Before you dive into submodules, you should probably be familiar with a basic understanding of Git.

For a general view of submodules read the [documentation](https://git-scm.com/book/en/v2/Git-Tools-Submodules), and then talk to a team member who has experience, it's pretty easy.

[This is also a good article](https://chrisjean.com/git-submodules-adding-using-removing-and-updating/) (if it
ever goes offline there is a copy saved [here](https://gitlab.com/solar-car/electrical/detailed-documentation/new-electrical-guide/uploads/fa463c945460ffe13c91fceb2a11e013/git_submodule.pdf)).

## Code Composer Studio 
To use this project in Code Composer Studio you need to be compiling your projects using [MSP430-GCC](http://www.ti.com/tool/MSP430-GCC-OPENSOURCE).

## Unit Tests 
To compile this project for unit tests, you need to be using a shell interface (i.e., not gcc on Windows). If you are on Windows it is recommended that you use [SubSystem for Windows](https://docs.microsoft.com/en-us/windows/wsl/install-win10) and install Ubuntu. 

You will need to have `make` and `gcc` installed. 

To build, run (from this directory) this command: 
```shell 
make <microcontroller> 
```

Where `<microcontroller>` is the name of the microcontroller directive used in the `registration.h` file (e.g, `make msp430f5529`). 

This will define the directive `__<MICROCONTROLLER>__` where `<MICROCONTROLLER>` is `<microcontroller>` converted to all capital letters.

After compilation, you will see a `<microcontroller>.test.out` file that you can then run to perform the unit tests. 

&nbsp;

# Data Types
The following table lists the data types (`typedef`s) defined by this library:

| Name | Underlying Type |
|------|-------|
|`int8_t`|`signed char`|
|`uint8_t`|`unsigned char`|
|`int16_t`|`short int`|
|`uint16_t`|`unsigned short int`|
|`int32_t`|`long int`|
|`uint32_t`|`unsigned long int`|
|`int64_t`|`long long int`|
|`uint64_t`|`unsigned long long int`|
|`vuint8_t`|`volatile unsigned char`|
|`vuint16_t`|`volatile unsigned short int`|
|&nbsp;|&nbsp;|
|`io_pin`|`uint8_t`|
|`bool`| Enum: `False`, `Failure`, `Busy`, `No`, or `Disable` <br/> `True`, `Success`, `Yes`, or `Enable`|
|`pin_mode`| Enum: `Input` or `Output`|
|`pin_level`| Enum: `Low` or `High`|
|`spi_bus`| Microcontrollers define how many SPI buses they have, will be in the format of `SPI_BUS_x`|
|&nbsp;|&nbsp;|
|`group_64`| Union. (see [file](datatypes.h)) |
|`can_message`| Struct. (see [file](datatypes.h)) |

These are all defined in [`datatypes.h`](datatypes.h).

&nbsp;

# Constants
The folling table lists the constants defined by this library:

| Name | Value |
|------|-------|
|`NULL`|`0x00`|
|`NOTHING`|`NULL`|
|`EMPTY`|`NULL`|
|`NO_PIN`|`NULL`|
|`NO_REGISTER`|`NULL`|
|`NO_PORT`|`NULL`|
|`NO_BIT`|`NULL`|
|`NO_MESSAGE`|`NULL`|
|`NO_VECTOR`|`NULL`|
|&nbsp;|&nbsp;|
|`CAN_OK`|`0x0001`|
|`CAN_RTR`|`0xFFFC`|
|`CAN_WAKE`|`0xFFFD`|
|`CAN_MERROR`|`0xFFFE`|
|`CAN_ERROR`|`0xFFFF`|
|`BIT0` - `BITF` | `0x0001` - `0x8000`|


&nbsp; 

# File Extensions 
Looking through this project you will see different file extensions, namely `.driver` and `.test`. 

These are needed because Code Composer Studio will compile any, and all `.c` files in the project, and we don't want the unit test stuff to be included in the firmware that gets put on microcontrollers, so this is the solution. 


&nbsp;

# Shout Outs
This project is possible by the awesome open source utilities by the team at [Throw The Switch](http://www.throwtheswitch.org/)

For unit testing, [Unity](http://www.throwtheswitch.org/unity) is used, ([see the LICENSE here](testing/unity/LICENSE)). 

[CException](http://www.throwtheswitch.org/cexception) is used for added exception handling ([see the LICENSE here](utils/exception/LICENSE)).