#include "spi.h"

/**
 * Setup for SPI hardware
 */
void spi_setup(io_pin mosi, io_pin miso, io_pin sck)
{
  setOutput(mosi);
  setOutput(miso);
  setOutput(sck);

  setHigh(mosi);
  setHigh(miso);
  setHigh(sck);
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
  spi_busy_check();

  return spi_get_data();
}
