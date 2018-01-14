# Driver Library Examples
This file contains examples on how to use this library, they are not files so you will hopefully type out the code instead of just copy and paste.

Each example assumes the following folder structure:
```
  - Project/
    - drivers/
      - [this library]
    - src/
      - [code]
    - includes/
      - [code header files]
```

&nbsp;

Each example is also setup around the MSP430F5529

&nbsp;

# LED Control
```c
// Project/src/main.c
#include "../drivers/solarcar.h"

#define LED_TO_TURN_ON  P2_7  // LED to turn on (and keep on) is on P2.7
#define LED_TO_FLASH    P2_6  // LED to flash is on P2.6


int main(void)
{
  // Configure LED pins as input
  inputPin(LED_TO_TURN_ON);
  inputPin(LED_TO_FLASH);

  // Turn on the one LED
  setPinHigh(LED_TO_TURN_ON);

  // Infinite loop
  while (True) {
    togglePin(LED_TO_FLASH); // Blink the LED

    __delay_cycles(1000000); // Delay so we can see the flash
  }

  return 0;
}
```