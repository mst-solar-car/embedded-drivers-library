# Microcontroller Drivers


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
