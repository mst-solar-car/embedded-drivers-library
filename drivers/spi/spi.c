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
void spi_setup(io_pin mosi, io_pin miso, io_pin sck)
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
}



/**
 * Transmit over SPI
 *
 * @param uint8_t   data    Data to send
 *
 * @return uint8_t  Data received from transmission
 */
uint8_t spi_transmit(uint8_t data)
{
    spi_busy_check();
    spi_send_data(data);
    spi_busy_check2();

    return spi_get_data();
}

