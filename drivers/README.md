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