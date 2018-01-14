# Solar Car Embedded Driver Library

This driver library is split up into multiple drivers. The table below
outlines the parts of this library. Each one includes a link to a more detailed
README file that outlines how that driver works, what functionality it provides
to the user, and so on.

| Driver | Description |
|:------:|-------------|
|[CAN](can/README.md)| Driver for communication over CAN. Just a wrapper around a CAN Controller driver |
|[CAN Controllers](can_controllers/README.md)|Device-specific drivers that are used by the CAN drivers to communicate over a CAN Bus |
|[Microcontrollers](microcontrollers/README.md)|Device-specific drivers for controlling pins and registers on a microcontroller|
|[SPI](spi/README.md)|Drivers that interface with the Microcontroller drivers for communication on a SPI Bus|
|[Pin Control](#pin-control-api)|Used to control state of pins on a microcontroller|
|[Register Maniuplation](#register-maniuplation-api)|Used for modifying registers on a microcontroller (probably only used in drivers)|
|[Bit Manipulation](#bit-manipulation-api)|Used for generic bit manipulation anywhere in program|


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
|`pin_mode`| Enum: `Input`, `Interrupt`, or `Output`|
|`pin_level`| Enum: `Low`, or `High`|
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

# Pin Control API
The following table lists the functions that can be used for controlling pins/registers on a device (please note that pin naming should be detailed in specific microcontroller driver documentation):

| Function Syntax | Description |
|-------------------|-----------|
|[`setPinMode(pin, mode)`| Configures `pin` in `mode` (`Input`, `Output`, or `Interrupt`)|
|`inputPin(pin)`| Alias for `setPinMode(pin, Input)`|
|`outputPin(pin)`| Alias for `setPinMode(pin, Output)`|
|`interruptPin(pin)`| Alias for `setPinMode(pin, Interrupt)`|
|&nbsp;|&nbsp;|
|`setPinLevel(pin, level)`| Sets the `pin` to the `level` (`High`, or `Low`)|
|`setPinHigh(pin)`| Alias for `setPinLevel(pin, High)`|
|`setPinLow(pin)`| Alias for `setPinLevel(pin, Low)`|
|&nbsp;|&nbsp;|
|`togglePinLevel(pin)`| Sets `pin` as `High` if it's `Low`, and vice-versa|
|`togglePin(pin)`| Alias for `togglePinLevel(pin)`|
|&nbsp;|&nbsp;|
|`readPin(pin)`| Reads the state of a pin, returns `High` or `Low`|
|`isPinHigh(pin)`| Alias for `(readPin(pin) == High)`|
|`isPinLow(pin)`| Alias for `(readPin(pin) == Low)`|

These are all defined in [`microcontroller.h`](microcontrollers/microcontroller.h).

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


These are all defined in [`microcontroller.h`](microcontrollers/microcontroller.h).

&nbsp;

# Register Manipulation API
The following table lists directives used for register manipulation. These are probably
not going to be used outside of microcontroller drivers very much. They all accept a *pointer to a register*:

| Function Syntax | Description |
|-----------------|-------------|
|`setRegister(reg, data)`| Alias for `*reg = data`|
|`setRegisterBitHigh(reg, bit)` | Alias for `setBitHigh(*reg, bit)`|
|`setRegisterBitLow(reg, bit)` | Alias for `setBitLow(*reg, bit)`|
|`toggleRegisterBit(reg, bit)` | Alias for `toggleBit(*reg, bit)`|
|&nbsp;|&nbsp;|
|`pinPort(pin)`| Returns the port number (`uint8_t`) that cooresponds to `pin`. **NO ERROR CHECKING**|
|`getPinPort(out, pin[, x])`| Alias for `out = pinPort(pin); if (out == NO_PORT) return x` -- Note that `x` is optional. |
|&nbsp;|&nbsp;|
|`pinBit(pin)`| Returns the BIT (`BITx`) that goes with `pin`. **NO ERROR CHECKING**|
|`getPinBit(out, pin[, x])`| Alias for `out = pinBit(pin); if (out == NO_BIT) return x` -- Note that `x` is optional.|
|&nbsp;|&nbsp;|
|`dirReg(port)`| Returns a pointer to the `dir` register for a certain `port` (**does not accept a pin**) **NO ERROR CHECKING**|
|`getDirReg(out, port[, x])`| Alias for `out = dirReg(port); if (out == NO_REGISTER) return x` -- Note that `x` is optional.|
|&nbsp;|&nbsp;|
|`outReg(port)`| Returns a pointer to the `out`(put) register for a certain `port` (**does not accept a pin**) **NO ERROR CHECKING**|
|`getOutReg(var, port[, x])`| Alias for `var = outReg(port); if (var == NO_REGISTER) return x` -- Note that `x` is optional.|
|&nbsp;|&nbsp;|
|`inReg(port)`| Returns a pointer to the `in`(put) register for a certain `port` (**does not accept a pin**) **NO ERROR CHECKING**|
|`getInReg(var, port[, x])`| Alias for `var = inReg(port); if (var == NO_REGISTER) return x` -- Note that `x` is optional.|
|&nbsp;|&nbsp;|
|`selReg(port)`| Returns a pointer to the `sel`(ect) register for a certain `port` (**does not accept a pin**) **NO ERROR CHECKING**|
|`getSelReg(out, port[, x])`| Alias for `out = selReg(port); if (out == NO_REGISTER) return x` -- Note that `x` is optional.|
|&nbsp;|&nbsp;|
|`iesReg(port)`| Returns a pointer to the `ies` (Interrupt Edge Select) register for a certain `port` (**does not accept a pin**) **NO ERROR CHECKING**|
|`getIESReg(out, port[, x])` | Alias for `out = iesReg(port); if (out == NO_REGISTER) return x` -- Note that `x` is optional.|
|&nbsp;|&nbsp;|
|`ieReg(port)`| Returns a pointer to the `ie` (Interrupt Enable) register for a certian `port` (**does not accept a pin**) **NO ERROR CHECKING**|
|`getIEReg(out, port[, x])`| Alias for `out = ieReg(port); if (out == NO_REGISTER) return x` -- Note that `x` is optional.|
|&nbsp;|&nbsp;|
|`ifgReg(port)`| Returns a pointer to the `ifg` (Interrupt Flag) register for a certain `port` (**does not accept a pin**) **NO ERROR CHECKING**|
|`getIFGReg(out, port[, x])`| Alias for `out = ifgReg(port); if (out == NO_REGISTER) return x` -- Note that `x` is optional.|

These are all defined in [`microcontroller.h`](microcontrollers/microcontroller.h).
