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

## Table of Contents

| Example |
|:-------:|
|[LED Control](#led-control)|
|[Reading Pins](#reading-pins)|
|[Sending CAN Messages](#sending-can-messages)|
|[Receiving CAN Messages](#receiving-can-messages)|
|[Manual Register Access](#register-access)|
|[Interrupts](#interrupts)|

&nbsp;


# LED Control
```c
// Project/src/main.c
#include "../drivers/solarcar.h"

#define LED_TO_TURN_ON  P2_7  // LED to turn on (and keep on) is on P2.7
#define LED_TO_FLASH    P2_6  // LED to flash is on P2.6


int main(void)
{
  // Configure LED pins as output
  outputPin(LED_TO_TURN_ON);
  outputPin(LED_TO_FLASH);

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

&nbsp;

# Reading Pins
```c
// Project/src/main.c
#include "../drivers/solarcar.h"

#define LED_SWITCH    P1_5  // Switch to turn on LED is on P1.5
#define LED           P1_6  // LED for switch is on P1.6

int main(void)
{
  // Configure pins
  inputPin(LED_SWITCH);
  outputPin(LED);

  setPinLow(LED); // Off by default

  while (True) {
    if (isPinHigh(LED_SWITCH)) {
      // Switch is ON, turn on the LED
      setPinHigh(LED);
    }
    else {
      // Switch is OFF, turn off the LED
      setPinLow(LED);
    }

    __delay_cycles(100000); // Delay
  }

  return 0;
}
```

&nbsp;

# Sending CAN Messages
```c
// Project/src/main.c
#include "../drivers/solarcar.h"

#define BOARD_CAN_ID    0x500   // CAN ID of this board

#define CAN_CS          P2_5    // CAN Chip Select
#define CAN_INT         P2_6    // CAN Interrupt Pin

// SPI Pins
#define SPI_MOSI        P4_1
#define SPI_MISO        P4_2
#define SPI_CLK         P4_3

int main(void)
{
  // Initialize SPI
  spi_setup(SPI_BUS_4, SPI_MOSI, SPI_MISO, SPI_CLK);

  // Initialize CAN
  can_setup(CAN_CS, CAN_INT);

  while (True) {
    // Create the new CAN Message
    can_new_msg->address = BOARD_CAN_ID;
    can_new_msg->data.data_u8[0] = 5;
    can_new_msg->data.data_u8[1] = 4;
    can_new_msg->data.data_u8[2] = 3;
    can_new_msg->data.data_u8[3] = 2;
    can_new_msg->data.data_u8[4] = 1;
    can_new_msg->data.data_u8[5] = 0;

    // Send messages
    can_transmit();

    __delay_cycles(10000000); // Delay
  }

  return 0;
}
```

&nbsp;

# Receiving CAN Messages
```c
// Project/src/main.c
#include "../drivers/solarcar.h"

#define BOARD_CAN_ID    0x500   // CAN ID of this board

#define CAN_CS          P2_5    // CAN Chip Select
#define CAN_INT         P2_6    // CAN Interrupt Pin

// SPI Pins
#define SPI_MOSI        P4_1
#define SPI_MISO        P4_2
#define SPI_CLK         P4_3

#define LED             P1_6    // LED to toggle when message received

int main(void)
{
  // Initialize SPI
  spi_setup(SPI_BUS_4, SPI_MOSI, SPI_MISO, SPI_CLK);

  // Initialize CAN
  can_setup(CAN_CS, CAN_INT);

  outputPin(LED); // Configure LED pin

  while (True) {
    // Get the next received CAN Message
    can_message* received = can_receive();
    if (received != NOTHING) {
      // Message was received!!!
      if (received->address == 0x200) {
        togglePin(LED); // :)
      }
    }
  }

  return 0;
}
```

```c
// Projects/drivers/user_config.h

// Filters are what IDs to receive
#define CAN_FILTER1         0x200
#define CAN_FILTER2         0x000
#define CAN_FILTER3         0x000
#define CAN_FILTER4         0x000
#define CAN_FILTER5         0x000
#define CAN_FILTER6         0x000

// Masks apply to filters (ask someone about it)
#define CAN_MASK1           0x000
#define CAN_MASK2           0x000

#default SPI_BUS            SPI_BUS_4
```


&nbsp;

# Register Access
```c
// Project/src/main.c
#include "../drivers/solarcar.h"

#define LED_PIN     P1_5  // LED

void main(void)
{
  uint8_t port;
  uint8_t bit;
  vuint8_t* dirRegister;

  // Get PORT and BIT
  getPinPort(port, LED_PIN); // port = pinPort(LED_PIN); if (port == NO_PORT) return;
  getPinBit(bit, LED_PIN); // bit = pinBit(LED_PIN); if (bit == NO_BIT) return;

  // Get direction register
  getDirReg(dirRegister, port); // dirRegister = dirReg(port); if (dirRegister == NO_REGISTER) return;

  // Manually configure LED_PIN as output
  setRegisterBitHigh(dirRegister, bit);
}
```

&nbsp;

# Interrupts
```c
// Project/src/main.c
#include "../drivers/solarcar.h"


#define DEBUG_LED_1 P6_6
#define DEBUG_LED_2 P6_7


void P2_5_ISR(void);


void main(void)
{
  attachInterrupt(P2_5);

  // Imagine that this example configures a system timer here

  while (True) {
    // Do nothing
  }
}

// Toggle an LED when an interrupt on P2.5 occurs
void P2_5_ISR(void)
{
  togglePin(DEBUG_LED_1);
}

// Interrupt for the timer
// Toggle an LED when the timer overflows
nonPinInterrupt(TIMER1_A0_VECTOR)
{
  togglePin(DEBUG_LED_2);
}
```