# Creating Microcontroller Drivers
This file will cover the basics of implementing the microcontroller interface
for a custom microcontroller drivers. Remember, that unless an operation is
SPECIFIC to a microcontroller, then you should not expose a function for it to the user.

The proper way to do this is to write a generic library for it that interfaces with
the microcontroller driver.

> **NOTE**: the manufacture probably provides a header file that you include in your programs for a microcontroller, this header file would define stuff such as register names, and constants. ONLY include the program is NOT running in unit test mode.

&nbsp;

## Structure
Your microcontroller drivers should be in their own folder, and should have the same name
as the model of the microcontroller.

You will then implement the files needed:
```
- microcontroller/
    - model_number/
        - interface.h
        - model_number.driver
        - model_number.mock
        - model_number.spec
        - model_number.tests
```

&nbsp;

## Functions
These functions are required (by the microcontroller interface) to be implemented with
every microcontroller driver:

| Syntax | Description |
|--------|-------------|
|`__microcontroller_spi_setup(spi_bus, mosi_pin, miso_pin, sck_pin)` | Initialize a SPI bus in microcontroller registers. |
|`__microcontroller_spi_transmit(spi_bus, data)` | Transmits data over a specified SPI Bus. |
|`__microcontroller_interrupts_configure(enable)` | Enable interrupts if `enable` is `True`, disable if `enable` is `False`. |
|`__microcontroller_initialization()`| This is called automagically by the library before the execution of `main()`. Use this to initialize pins, clock, all that generic jazz--nothing that requires user configuration though (like SPI). |

These functions should be implemented in your `model_number.driver` file (and do not
need to be declared in the interface file for your microcontroller).

&nbsp;

## Spec File
The `model_number.spec` file tells the library all about your microcontroller.

> Honestly, it's preprocessor gore and is literal magic. 🙃

The first thing you should do in this file is:

```c
#include "../fixture.h"
```

The `fixture.h` file is what defines the crazy directives that you're about to use to
define the specs of your microcontroller.

This table shows fixtures provided by `fixture.h` that you **need** to use in your `.spec` file:

| Fixture Syntax | Description |
|---------|-------------|
|`CLOCK_SPEED_HZ(speed)` | Defines `MC_CLOCK_SPEED_HZ` for use anywhere in the library, it will be set equal to `speed`. |
| `REGISTER_PINS(number_of_pins)` | Defines `PIN1` through `PINnumber_of_pins` for use in the user program or anywhere really. <br/><br/>This also defines `MC_NUMBER_OF_PINS` which is set equal to `number_of_pins`. |
| `REGISTER_PORTS(`<br/>`(1, *dir_register, *in_register[, *sel_register, *ies_register, *ie_register, *ifg_register]),`<br/>`...,`<br/>`(n, *dir_register, *in_register[, *sel_register, *ies_register, *ie_register, *ifg_register])`<br/>`)` | Registers each Port (defines `PORT1` through `PORTn`) as well as all the registers associated with ach port. These are used to control output pins. |
|`REGISTER_PINS_FOR_PORT(`<br/>`(1, bit0_pin, bit1_pin, ..., bit7_pin),`<br/>`...,`<br/>`(n, bit0_pin, bit1_pin, ..., bit7_pin)`<br/>`)` | Used to map a bit on a port to a pin on the microcontroller, if a bit pin is not included, it will not be useable in the program and will cause an error. <br/>You are able to use `PINx` here, or just integers corresponding to the pin number. |
| `REGISTER_SPI_BUSES(number_of_spi_buses)` | Defines `SPI_BUS_1` through `SPI_BUS_number_of_spi_buses`. <br/>This also defines `MC_NUMBER_OF_SPI_BUSES` which is set to `number_of_spi_buses`. |
|`REGISTER_INTERRUPTABLE_PORTS(`<br/>`(PORT1, PORT1_VECTOR),`<br/>`...,`<br/>`(PORTn, PORTn_VECTOR)`<br/>`)` | This will allow for ports to be interruptable and register them with the interrupts driver. |

For an example of this, see the [`.spec` file in this MSP430F5529 driver folder](msp430f5529/msp430f5529.spec).


&nbsp;

## Mock File
You **need** to have a `.mock` file for your microcontroller so you can perform unit tests
for the code you've written.

In this file, the first thing you should do is:
```c
#include "../../testing/mock.h"
```
Including `mock.h` will provide you with the fixture needed for registering mock values and mock
registers.

> **NOTE**: this file (the .mock file) is only included when you are unit testing.
> It's goal is to mock registers and constants that are provided by the linker when
> compiling and flashing to target hardware. That way, you do not need to change how your
> code is written (using different register names, etc...) to make it work on target hardware and unit testing.

This table shows functions provided by the `mock.h` fixture for use in this file:

| Fixture Syntax | Description |
|----------------|-------------|
|`MOCK_REGISTERS(reg1, reg2, ..., regn)` | When unit testing these "registers" will be created for these registers that you can use to verify values placed into them in unit testing. They can be named anything, but they should definitely be named what they would be when running on target hardware. |
| `MOCK_CONSTANTS(const1 = const1_value, ..., constn = constn_value)` | When unit testing, constants will be created that are assigned the values specified. They can be named anything, but they should definitely be named what they would be when running on target hardware. <br/>You shouldn't need to check these during unit testing, they are so code will continue to work despite constants not being defined as they would be when running on target hardware. |

Anything else that is needed should be defined in this file without using a fixture,
use things such as `#define`, `const`, or `enum`.

For an example of the `.mock` file, see [the one in the msp430f5529 directory](msp430f5529/msp430f5529.mock).


&nbsp;

## Interface File
If your microcontroller has a feature that currently does not have a generic driver,
your first thought should be to write a generic driver for it.

But, if that feature is not supported by the majority of microcontrollers, or would be difficult
to write a generic driver for it, then you should put it in the microcontroller interface file.


