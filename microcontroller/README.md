# Microcontroller
The microcontroller drivers are really the heart of this library.
They are what everything ultimately interacts with.


Ideally, the goal of this library, is to be able to just write new microcontroller
drivers, that implement the microcontroller interface, and this library would be ready to run on that microcontroller.

&nbsp;

# Functions
This library, `microcontroller/interface.h` **DOES NOT** expose any functions that
the user should be callling.

However, if certain microcontroller driver implementations want/need to expose their own specific functions through their interface (`microcontroller/MICROCONTROLLER/interface.h`) then that is perfectly fine.

&nbsp;

# Registration
The [registration.h](registration.h) file is what determines which microcontroller to use, this should be done by using directives that the compiler defines, or the user sets (only if needed).

See it for examples.

&nbsp;

# Creating a Microcontroller Driver
Please see [this file](CREATING_MICROCONTROLLER_DRIVERS.md) for details on what is
required to implement a microcontroller driver implementation.
