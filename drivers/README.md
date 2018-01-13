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


# Directive Configuration
The drivers in this library should use little-to-no preprocessor (`#define`)
configuration constants.

The only exception is when it makes interfacing with drivers easier, and they are
configuration items that should not need to be easily changed (such as CAN filters, etc...).

Anything that needs a pin for configuration should accept it in the `driver_setup()` function,
**NOT AS A DIRECTIVE**.

For when directive configuration is desired, the directives should be declared inside the [`user_config.h`](user_config.h) file.

The cooresponding README to each driver will document any and all `#define` directives that can go in the
`user_config.h` file.