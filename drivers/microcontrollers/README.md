# Microcontroller Drivers
The Microcontroller Drivers are designed to be as robust and flexible as possible.

Ideally, you could just write new drivers for another microcontroller and continue
using the same code that was written for another microcontroller.

But, since at the time of writing these drivers (Dec. 2017/Jan. 2018) we only used the `MSP430F5529`, the generic library might be a little biased.

So, if ever switching to a new microcontroller write drivers based on the [`MSP430f5529` drivers](msp430f5529/) and modify accordingly.

&nbsp;

| Section |
|:-------:|
|[About](#about)|
|[Pin Control API](#pin-control-api)|
|[Register Manipulation API](#register-manipulation-api)|
|[Implementing Microcontroller Drivers](#microcontroller-interface)|

&nbsp;


# About
The Microcontroller Drivers have two parts: a `generic pin control library` and then a microcontroller-specific drivers.

The `generic pin control library` is what defines the [`Pin Control API`](#pin-control-api), it uses the microcontroller-specific drivers in-order to control pins and registers.

In the microcontroller-specific drivers, all that the user needs to do is populate some arrays with pointers to registers in memory,the `microcontroller_setup()` function that runs *before the main() function*, and then generic spi, watchdog, and interrupt stuff.

The [`importer.h`](importer.h) file is what loads the microcontroller-specific drivers. Since Code Composer Studio knows the target microcontroller, it automagically defines constants that represent what the target is. This can be used to make this library portable. By adding another `#elif defined(__MY_MICROCONTROLLER__)` and then load the microcontroller-specific `.h` file, you'll get this modular functionality that seems pretty cool.

&nbsp;

# Pin Control API
The following table lists the functions that can be used for controlling pins/registers on a device (please note that pin naming should be detailed in specific microcontroller driver documentation):

| Function Syntax | Description |
|-------------------|-----------|
|`setPinMode(pin, mode)`| Configures `pin` in `mode` (`Input`, `Output`, or `Interrupt`)|
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


&nbsp;

# Microcontroller Interface
This section will talk about *what* you have to define in order to have a functional driver for a certain microcontroller.

Again, this was written when we only used the `MSP430F5529`, so another microcontroller might label things differently, or not even have some features. This library tries to accomidate for that but might need further modification for other microcontrollers.


If any of the directives (not the arrays) listed in the following sections are not defined, then you will get an error at compile time.


&nbsp;

## Register Arrays
The heart of the microcontroller drivers revolves around the definition of `register arrays` in the microcontroller-specific code.

These arrays contain pointers to certain registers needed to control pins, interrupts, etc...

| Array Name | Description |
|:----------:|-------------|
|`dir_registers`| Registers for marking pins as `Input` or `Output`|
|`out_registers`| Registers for setting the state (`High` or `Low`) for pins configured as `Output` |
|`in_registers`| Registers for reading value of pins marked as `Input`|
|`sel_registers`| I don't really know what these registers do, but SPI uses them|
|`ies_registers`| Registers for configuring Interrupt Edge Select for interruptable pins |
|`ie_registers`| Registers for configuring Interrupt Enable for interruptable pins |
|`ifg_registers`| Registers for getting Interrupt Flags |
|&nbsp;|&nsbp;|
|`port_map`|This array *does not* contain pointers. It should have the same number of elements as pins on the microcontroller, and should map to a `port` that can be used in the other arrays. |
|&nbsp;|&nbsp;|
|`bit_map`| This array *does not* contain pointers. It should have the same number of elements as pins on the microcontroller, and should map to a `bit` that the pin maps to in a register. |


&nbsp;

## Watchdog Timer
First off, if the microcontroller does not have a watchdog timer, then you need to have `#define NO_WATCHDOG` inside your header file for the microcontroller.

If it does have a watchdog timer then you need to define the following directives (usually one-liners):

| Directive | Description |
|-----------|-------------|
|`watchdog_enable()`| Starts the Watchdog Timer|
|`watchdog_disable()`| Disables the Watchdog Timer|
|`watchdog_pet()`| Resets the Watchdog Timer to avoid reset|


&nbsp;

## Interrupts
First off, if the microcontroller does not support interrupts (weird), then you need to have `#define NO_INTERRUPTS` in your header file.

If it does have interrupts, then you need the following directives:

| Directive | Description |
|-----------|-------------|
|`interrupts_enable()`| Enables interrupts on the system |
|`interrupts_disable()`| Disables interrupts on the system |

&nbsp;

## SPI
First off, if the microcontroller does not support SPI (weird), then you need to have `#define NO_SPI` in your header file.

If it does have SPI (it should), then you need the following directives:

| Directive | Description |
|-----------|-------------|
|`spi_busy_check()`| Checks if SPI is busy (*before* sending data)|
|`spi_busy_check2()`| Checks if SPI is busy (*after* sending data)|
|`spi_send_data(data)`| Moves `data` into the register for SPI transmission|
|`spi_get_data()`| Should just evalute to the SPI RX register|


&nbsp;

## Setup Function
The microcontroller-specific code should define a function called `microcontroller_setup`, it should have the following signature:

`void microcontroller_setup(void)`

This function will run *before* the `main()` function runs.

It should do the following:

- Disable watchdog (if applicable)
- Set default state for pins
- Enable interrupts (if applicable)
- Configure the clock (if applicable)
- Any other configuration that the user shouldn't need to do