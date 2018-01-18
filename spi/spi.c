/*
 * spi.c
 * SPI drivers
 *
 *  Created on: Dec 18, 2017
 *      Author: mwrouse
 */
#include "spi.h"

/**
 * Setup for SPI hardware
 */
void spi_setup(spi_bus bus, io_pin mosi, io_pin miso, io_pin sck)
{
    uint8_t port;
    vuint8_t* reg;

    port = pinPort(mosi);
    reg = selReg(port);
    setRegisterBitHigh(reg, pinBit(mosi));

    port = pinPort(miso);
    reg = selReg(port);
    setRegisterBitHigh(reg, pinBit(miso));

    port = pinPort(sck);
    reg = selReg(port);
    setRegisterBitHigh(reg, pinBit(sck));

    // Setup special microcontroller registers
    microcontroller_spi_setup(bus);
}



/**
 * Transmit over SPI
 *
 * @param spi_bus   bus     The bus to send Data over
 * @param uint8_t   data    Data to send
 *
 * @return uint8_t  Data received from transmission
 */
uint8_t spi_transmit(spi_bus bus, uint8_t data)
{
  return microcontroller_spi_transmit(bus, data);
}

