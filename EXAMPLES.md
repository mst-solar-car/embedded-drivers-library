# Examples
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
|[Basic Pin Control](#pin-control)|
|[SPI](#spi)|
|[Receiving CAN Messages](#receiving-can-messages)|
|[Sending CAN Message](#sending-can-messages)|
|[Interrupts](#interrupts)|




&nbsp;


# Pin Control
```c
#include "../drivers/library.h"

#define BUTTON      P2_7
#define BUTTON_LED  P4_7
#define STATUS_LED  P1_0

int main(void)
{
  pin_set_mode(BUTTON, Input);
  pin_set_mode(BUTTON_LED, Output);
  pin_set_mode(STATUS_LED, Output);

  while (True)
  {
    /* Turn on BUTTON_LED if button is pressed */
    if (pin_read(BUTTON) == Low)
      pin_set_level(BUTTON_LED, High);
    else
      pin_set_level(BUTTON_LED, Low);

    /* Flash the Status LED */
    pin_toggle(STATUS_LED);

    delay_millis(1000); /* 1 second delay */
  }

  return 0;
}
```

&nbsp;

# SPI
```c
#include "../drivers/library.h"

#define SPI_MOSI  P4_1
#define SPI_MISO  P4_2
#define SPI_CLK   P4_3

int main(void)
{
  spi_setup(SPI_BUS_4, SPI_MOSI, SPI_MISO, SPI_CLK);

  while (True)
  {
    uint8_t received = spi_transmit(SPI_BUS_4, 0x42);

    if (received != NULL)
    {
      /* Something was received! */
    }

    delay_millis(5000); /* 5 second delay */
  }

  return 0;
}
```

&nbsp;

# Receiving CAN Messages
```c
#include "../drivers/library.h"

#define BMS_CAN_ID    0x100
#define DIB_CAN_ID    0x200

#define CAN_CS          P2_5    // CAN Chip Select
#define CAN_INT         P2_6    // CAN Interrupt Pin

#define SPI_MOSI  P4_1
#define SPI_MISO  P4_2
#define SPI_CLK   P4_3

int main(void)
{
  spi_setup(SPI_BUS_4, SPI_MOSI, SPI_MISO, SPI_CLK);

  can_accept(BMS_CAN_ID, DIB_CAN_ID);
  can_setup(SPI_BUS_4, CAN_CS, CAN_INT);

  while (True)
  {
    can_message* msg = can_receive();
    if (msg != NO_MESSAGE)
    {
      if (msg->address == BMS_CAN_ID)
      {
        /* Yay! */
      }
      else if (msg->address == DIB_CAN_ID)
      {
        /* Yay! */
      }
    }

    delay_millis(1000); /* 1 second delay */
  }

  return 0;
}

```

&nbsp;

# Sending CAN Messages
```c
#include "../drivers/library.h"

#define MY_CAN_ID     0x500
#define BMS_CAN_ID    0x100
#define DIB_CAN_ID    0x200

#define CAN_CS          P2_5    // CAN Chip Select
#define CAN_INT         P2_6    // CAN Interrupt Pin

#define SPI_MOSI  P4_1
#define SPI_MISO  P4_2
#define SPI_CLK   P4_3

int main(void)
{
  spi_setup(SPI_BUS_4, SPI_MOSI, SPI_MISO, SPI_CLK);

  can_accept(BMS_CAN_ID, DIB_CAN_ID);
  can_setup(SPI_BUS_4, CAN_CS, CAN_INT);

  while (True)
  {
    /* Construct the message */
    can_new_msg.address = MY_CAN_ID;
    can_new_msg.data.data_u8[0] = 5;
    can_new_msg.data.data_u8[1] = 4;
    can_new_msg.data.data_u8[2] = 3;
    can_new_msg.data.data_u8[3] = 2;
    can_new_msg.data.data_u8[4] = 1;
    can_new_msg.data.data_u8[5] = 0;

    can_transmit();

    delay_millis(10000); /* 10 second delay */
  }

  return 0;
}
```

&nbsp;

# Pin Interrupts
```c
#include "../drivers/library.h"

#define ISR_LED   P1_0

void pin_ISR(void)
{
  pin_toggle(ISR_LED);
}

int main(void)
{
  interrupts_enable();

  pin_set_mode(ISR_LED, Output);

  interrupt_attach(P2_5, pin_ISR); /* Attach interrupt ISR */

  while (True)
  {
    /* Nothing */
  }

  return 0;
}


/* This syntax is an alternative to interrupt_attach */
interrupt_pin_ISR(P2_1)
{
  /* ISR for P2.1 */
}

/* Syntax for creating a non-pin interrupt */
interrupt_ISR(TIMER_A0_VECTOR)
{
  /* Non-Pin ISR */
}
```