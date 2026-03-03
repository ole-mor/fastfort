#include "./i2c.h"
#include <stdio.h>

int8_t i2c_init(uint8_t bus_id, uint32_t frequency) {
    printf("[SIM] I2C Init Bus: %u, Freq: %u\n", bus_id, frequency);
    return 0;
}

int8_t i2c_read(uint8_t bus_id, uint8_t addr, uint8_t* data, uint16_t len) {
    printf("[SIM] I2C Read Bus: %u, Addr: 0x%02X, Len: %u\n", bus_id, addr, len);
    for (uint16_t i = 0; i < len; i++) {
        data[i] = 0x00;
    }
    return 0;
}

int8_t i2c_write(uint8_t bus_id, uint8_t addr, const uint8_t* data, uint16_t len) {
    printf("[SIM] I2C Write Bus: %u, Addr: 0x%02X, Data: ", bus_id, addr);
    for (uint16_t i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
    return 0;
}

int8_t i2c_write_read(uint8_t bus_id, uint8_t addr, uint8_t reg, uint8_t* data, uint16_t len) {
    printf("[SIM] I2C Write/Read Bus: %u, Addr: 0x%02X, Reg: 0x%02X, Len: %u\n", bus_id, addr, reg, len);
    for (uint16_t i = 0; i < len; i++) {
        data[i] = 0x00;
    }
    return 0;
}
