#include "i2c.h"
#include <Arduino.h>
#include <Wire.h>

static TwoWire* buses[] = {&Wire, &Wire1};

int8_t i2c_init(uint8_t bus_id, uint32_t baudrate) {
    buses[bus_id]->begin();
    buses[bus_id]->setClock(baudrate);
    return 0;
}

int8_t i2c_deinit(uint8_t bus_id) {
    buses[bus_id]->end();
    return 0;
}

int8_t i2c_write(uint8_t bus_id, uint8_t addr, const uint8_t* data, uint16_t len) {
    buses[bus_id]->beginTransmission(addr);
    buses[bus_id]->write(data, len);
    buses[bus_id]->endTransmission();
    return 0;
}

int16_t i2c_read(uint8_t bus_id, uint8_t addr, uint8_t* buf, uint16_t len) {
    buses[bus_id]->requestFrom(addr, (uint8_t)len);
    uint16_t i = 0;
    while (buses[bus_id]->available() && i < len) {
        buf[i++] = buses[bus_id]->read();
    }
    return i;
}

int8_t i2c_write_reg(uint8_t bus_id, uint8_t addr, uint8_t reg, uint8_t value) {
    buses[bus_id]->beginTransmission(addr);
    buses[bus_id]->write(reg);
    buses[bus_id]->write(value);
    buses[bus_id]->endTransmission();
    return 0;
}

int8_t i2c_read_reg(uint8_t bus_id, uint8_t addr, uint8_t reg, uint8_t* value) {
    buses[bus_id]->beginTransmission(addr);
    buses[bus_id]->write(reg);
    buses[bus_id]->endTransmission(false);
    buses[bus_id]->requestFrom(addr, (uint8_t)1);
    if (buses[bus_id]->available()) {
        *value = buses[bus_id]->read();
        return 0;
    }
    return -1;
}

int8_t i2c_flush(uint8_t bus_id) {
    // Wire does not have explicit flush
    return 0;
}
