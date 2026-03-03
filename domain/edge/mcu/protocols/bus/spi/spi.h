#ifndef SPI_H
#define SPI_H

#include <stdint.h>

int8_t spi_init(uint8_t bus_id, uint32_t frequency, uint8_t mode);
int8_t spi_transfer(uint8_t bus_id, uint8_t cs_pin, const uint8_t* tx_data, uint8_t* rx_data, uint16_t len);
int8_t spi_write(uint8_t bus_id, uint8_t cs_pin, const uint8_t* data, uint16_t len);
int8_t spi_read(uint8_t bus_id, uint8_t cs_pin, uint8_t* data, uint16_t len);

#endif
