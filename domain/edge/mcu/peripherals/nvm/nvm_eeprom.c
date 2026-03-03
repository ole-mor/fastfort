#include "nvm.h"
#include "i2c.h"  // platform i2c driver

#define EEPROM_ADDR 0x50

void nvm_init(void) {
    i2c_init();
}

void nvm_read(uint32_t offset, void *buf, size_t len) {
    i2c_write_addr(EEPROM_ADDR, offset);
    i2c_read(EEPROM_ADDR, buf, len);
}

void nvm_write(uint32_t offset, const void *buf, size_t len) {
    i2c_write_addr(EEPROM_ADDR, offset);
    i2c_write(EEPROM_ADDR, buf, len);
}

void nvm_erase(uint32_t offset, size_t len) {
    uint8_t *empty = calloc(1, len);
    nvm_write(offset, empty, len);
    free(empty);
}
