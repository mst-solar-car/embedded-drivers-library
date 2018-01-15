# Solar Car Embedded Driver Library

This driver library is split up into multiple drivers. The table below
outlines the parts of this library. Each one includes a link to a more detailed
README file that outlines how that driver works, what functionality it provides
to the user, and so on.

| Driver | Description |
|:------:|-------------|
|[Microcontrollers](microcontrollers/README.md)|Device-specific drivers for controlling pins and registers on a microcontroller|
|[CAN](can/README.md)| Driver for communication over CAN. Just a wrapper around a CAN Controller driver |
|[CAN Controllers](can_controllers/README.md)|Device-specific drivers that are used by the CAN drivers to communicate over a CAN Bus |
|[SPI](spi/README.md)|Drivers that interface with the Microcontroller drivers for communication on a SPI Bus|
|[Bit Manipulation](#bit-manipulation-api)|Used for generic bit manipulation anywhere in program|
|[Examples](EXAMPLES.md)|Minimal-code examples for getting a hang of this library|


# User Configuration
The drivers in this library should use little-to-no preprocessor (`#define`)
configuration constants.

The only exception is when it makes interfacing with drivers easier, and they are
configuration items that should not need to be easily changed (such as CAN filters, etc...).

Anything that needs a pin for configuration should accept it in the `driver_setup()` function,
**NOT AS A DIRECTIVE**.

For when directive configuration is desired, the directives should be declared inside the [`user_config.h`](user_config.h) file.

The cooresponding README to each driver will document any and all `#define` directives that can go in the
`user_config.h` file.


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
|`bool`| Enum: `False`, `Failure`, `Busy`, `True`, or `Success`|
|`pin_mode`| Enum: `Input` or `Output`|
|`pin_level`| Enum: `Low` or `High`|
|&nbsp;|&nbsp;|
|`group_64`| Union. (see file) |
|`can_message`| Struct. (see file) |

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

&nbsp;

# Bit Manipulation API
The following table lists directives used for easily manipulating bits:

| Function Syntax | Description |
|-----------------|-------------|
|`setBitHigh(data, bit)` | Alias for `(data |= bit)`|
|`setBitLow(data, bit)`| Alias for `(data &= ~bit)`|
|`toggleBit(data, bit)`| Alias for `(data ^= bit)`|
|`getBit(data, bit)`| Alias for `(data & bit)`|
|&nbsp;|&nbsp;|
|`isBitHigh(data, bit)`| Alias for `(getBit(data, bit) != 0x00)`|
|`isBitLow(data, bit)`| Alias for `(getBit(data, bit) == 0x00)`|
|&nbsp;|&nbsp;|
|`leftShift(data, n)` | Alias for `((uint8_t)(data << n))`|
|`rightShift(data, n)`| Alias for `((uint8_t)(data >> n))`|


These are all defined in [`utils.h`](utils.h).

&nbsp;

