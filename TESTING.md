# Unit Testing
This library has been verified functional by the use of [Unit Tests](https://gitlab.com/solar-car/electrical/detailed-documentation/new-electrical-guide/wikis/unit-testing-c).

You are encouraged to write Unit Tests on your project and run them with the built-in unit testing framework included in this library.

Please see the terminology section of [this page](https://gitlab.com/solar-car/electrical/detailed-documentation/new-electrical-guide/wikis/unit-testing-c#concepts-and-terminology) for definitions of terms used in this readme.


&nbsp;

# Requirements
You need to have a Linux (or Mac?) to run these unit tests. If you are running Windows then you can use [Linux Subsystem on Windows](https://docs.microsoft.com/en-us/windows/wsl/install-win10).

You will also need the following compiler: `gcc`.

> Note: The only reason Linux is needed is because the makefile uses Linux shell commands. If you can convert the makefile to function properly on both Windows and Linux then you would the best.


&nbsp;

# Compiling Unit Tests
If this library has more than one microprosseor on it then you will need to compile one time for every microprocessor.

To compile, run the command: `make [microcontroller]` where `[microcontroller]` is the name of the module folder inside the `microcontroller` folder.

This will produce the file `[microcontroller].test.out` (assuming there are no errors).

Then to run the compiled file just use the `./[microcontroller].test.out` command.

&nbsp;

**Example**: `make msp430f5529` will compile for the `MSP430F5529` and produce a file named `msp430f5529.test.out`. Running `./msp430f5529.test.out` will run all the unit tests that were compiled.


&nbsp;

# Custom Unit Test Files
Similar to how this library uses `.driver` files for drivers, all files with the `.tests` extension contain unit tests.

It is best to have a unit test file (group) for each module you write, and have them in the same folder.

When you write your own test files you will also need to include a function that is responsible for running *all* of your custom test groups.

This function should be in a `.tests` file and look like this:

```c
#include "../drivers/library.h"
#include "../drivers/testing/framework.h"

CUSTOM_TESTS()
{
    // Run your groups here with RUN_GROUP(group_name)
}
```

> Note: that when compiling using GCC on the command line all `#include`s need to be **RELATIVE** to the current file path.

&nbsp;

# .c File Gotcha
The only `.c` file that the makefile will compile is this `library.c` from this library.

So, when writing tests for your modules you will need to `#include` the `.c` file that goes along with your module in your `.tests` file for that module.

&nbsp;

# Framework
As mentioned before this library has a built-in unit testing framework.

[Read more about it here](testing/README.md).

# Examples
To see examples of unit tests just look at the tests for the drivers in this library.

Just remember that some of them are really simple (SPI), and some of them are rather complex (MCP2515).



