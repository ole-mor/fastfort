#ifndef SPI_H
#define SPI_H

#include <stdint.h>

int8_t  spi_init(uint8_t bus_id, uint32_t baudrate);
int8_t  spi_deinit(uint8_t bus_id);
int8_t  spi_select(uint8_t bus_id, uint8_t cs_pin);
int8_t  spi_deselect(uint8_t bus_id, uint8_t cs_pin);
int8_t  spi_write(uint8_t bus_id, const uint8_t* data, uint16_t len);
int16_t spi_read(uint8_t bus_id, uint8_t* buf, uint16_t len);
int8_t  spi_transfer(uint8_t bus_id, const uint8_t* tx, uint8_t* rx, uint16_t len);
int8_t  spi_flush(uint8_t bus_id);

#endif
