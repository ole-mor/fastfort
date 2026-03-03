#ifndef I2C_H
#define I2C_H

#include <stdint.h>

int8_t i2c_init(uint8_t bus_id, uint32_t frequency);
int8_t i2c_read(uint8_t bus_id, uint8_t addr, uint8_t* data, uint16_t len);
int8_t i2c_write(uint8_t bus_id, uint8_t addr, const uint8_t* data, uint16_t len);
int8_t i2c_write_read(uint8_t bus_id, uint8_t addr, uint8_t reg, uint8_t* data, uint16_t len);

#endif
