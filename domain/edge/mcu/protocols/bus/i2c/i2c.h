#ifndef I2C_H
#define I2C_H

#include <stdint.h>

int8_t  i2c_init(uint8_t bus_id, uint32_t baudrate);
int8_t  i2c_deinit(uint8_t bus_id);
int8_t  i2c_write(uint8_t bus_id, uint8_t addr, const uint8_t* data, uint16_t len);
int16_t i2c_read(uint8_t bus_id, uint8_t addr, uint8_t* buf, uint16_t len);
int8_t  i2c_write_reg(uint8_t bus_id, uint8_t addr, uint8_t reg, uint8_t value);
int8_t  i2c_read_reg(uint8_t bus_id, uint8_t addr, uint8_t reg, uint8_t* value);
int8_t  i2c_flush(uint8_t bus_id);

#endif
