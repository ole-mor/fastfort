#include "i2c.h"
#include "hardware/i2c.h"

static i2c_inst_t* buses[] = {i2c0, i2c1};

int8_t i2c_init(uint8_t bus_id, uint32_t baudrate) {
    i2c_init(buses[bus_id], baudrate);
    return 0;
}

int8_t i2c_deinit(uint8_t bus_id) {
    i2c_deinit(buses[bus_id]);
    return 0;
}

int8_t i2c_write(uint8_t bus_id, uint8_t addr, const uint8_t* data, uint16_t len) {
    int result = i2c_write_blocking(buses[bus_id], addr, data, len, false);
    return result == PICO_ERROR_GENERIC ? -1 : 0;
}

int16_t i2c_read(uint8_t bus_id, uint8_t addr, uint8_t* buf, uint16_t len) {
    int result = i2c_read_blocking(buses[bus_id], addr, buf, len, false);
    return result == PICO_ERROR_GENERIC ? -1 : (int16_t)len;
}

int8_t i2c_write_reg(uint8_t bus_id, uint8_t addr, uint8_t reg, uint8_t value) {
    uint8_t buf[2] = {reg, value};
    return i2c_write(bus_id, addr, buf, 2);
}

int8_t i2c_read_reg(uint8_t bus_id, uint8_t addr, uint8_t reg, uint8_t* value) {
    i2c_write_blocking(buses[bus_id], addr, &reg, 1, true);  // true = keep control of bus
    int result = i2c_read_blocking(buses[bus_id], addr, value, 1, false);
    return result == PICO_ERROR_GENERIC ? -1 : 0;
}

int8_t i2c_flush(uint8_t bus_id) {
    // Pico SDK I2C is blocking, no flush needed
    return 0;
}
