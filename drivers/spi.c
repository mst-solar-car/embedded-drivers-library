#include "solarcar_spi.h"

/**
 * Setup for SPI hardware
 */
void spi_setup() {

    P4SEL |= MOSI + MISO + SCK;

    UCB1CTL1  = UCSWRST;    //Hold the device in a reset state while we configure
    UCB1CTL0  = 0x69;       //SPI mode 11, MSB first, 8 bit data, 3pin master synchronous mode
    UCB1CTL1 |= UCSSEL_3;       //SPI clock (BRCLK) source = SMCLK
    UCB1BR1   = 0x00;       //Set the high bit of the baud rate generator
    UCB1BR0   = 0x14;       //Set the low bit of the baud rate generator (SMCLK / 20 == 1MHz SPI)
    //UCB0IE   |= 0x04;     //Enable interrupts
    UCB1CTL1 &= ~UCSWRST;   //Release the bus from reset state
}


/**
 * Transmit over SPI
 *
 * @param uint8_t   data    Data to send
 *
 * @return uint8_t  Data received from transmission
 */
uint8_t spi_transmit(uint8_t data) {
    while((UCB1STAT & BIT1) != 0);

    UCB1TXBUF = data;
    while((UCB1STAT & BIT0) != 0);

    return UCB1RXBUF;
}
