#include "spi.h"
#include <Arduino.h>
#include <SPI.h>

static SPIClass* buses[] = {&SPI};

int8_t spi_init(uint8_t bus_id, uint32_t baudrate) {
    buses[bus_id]->begin();
    buses[bus_id]->beginTransaction(SPISettings(baudrate, MSBFIRST, SPI_MODE0));
    return 0;
}

int8_t spi_deinit(uint8_t bus_id) {
    buses[bus_id]->endTransaction();
    buses[bus_id]->end();
    return 0;
}

int8_t spi_select(uint8_t bus_id, uint8_t cs_pin) {
    digitalWrite(cs_pin, LOW);
    return 0;
}

int8_t spi_deselect(uint8_t bus_id, uint8_t cs_pin) {
    digitalWrite(cs_pin, HIGH);
    return 0;
}

int8_t spi_write(uint8_t bus_id, const uint8_t* data, uint16_t len) {
    buses[bus_id]->transfer((void*)data, len);
    return 0;
}

int16_t spi_read(uint8_t bus_id, uint8_t* buf, uint16_t len) {
    for (uint16_t i = 0; i < len; i++) {
        buf[i] = buses[bus_id]->transfer(0x00);
    }
    return len;
}

int8_t spi_transfer(uint8_t bus_id, const uint8_t* tx, uint8_t* rx, uint16_t len) {
    for (uint16_t i = 0; i < len; i++) {
        rx[i] = buses[bus_id]->transfer(tx[i]);
    }
    return 0;
}

int8_t spi_flush(uint8_t bus_id) {
    // SPI is synchronous, no flush needed
    return 0;
}
