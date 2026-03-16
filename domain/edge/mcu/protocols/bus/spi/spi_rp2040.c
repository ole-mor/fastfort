#include "spi.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"

static spi_inst_t* buses[] = {spi0, spi1};

int8_t spi_init(uint8_t bus_id, uint32_t baudrate) {
    spi_init(buses[bus_id], baudrate);
    return 0;
}

int8_t spi_deinit(uint8_t bus_id) {
    spi_deinit(buses[bus_id]);
    return 0;
}

int8_t spi_select(uint8_t bus_id, uint8_t cs_pin) {
    gpio_put(cs_pin, 0);
    return 0;
}

int8_t spi_deselect(uint8_t bus_id, uint8_t cs_pin) {
    gpio_put(cs_pin, 1);
    return 0;
}

int8_t spi_write(uint8_t bus_id, const uint8_t* data, uint16_t len) {
    spi_write_blocking(buses[bus_id], data, len);
    return 0;
}

int16_t spi_read(uint8_t bus_id, uint8_t* buf, uint16_t len) {
    spi_read_blocking(buses[bus_id], 0x00, buf, len);
    return len;
}

int8_t spi_transfer(uint8_t bus_id, const uint8_t* tx, uint8_t* rx, uint16_t len) {
    spi_write_read_blocking(buses[bus_id], tx, rx, len);
    return 0;
}

int8_t spi_flush(uint8_t bus_id) {
    // Pico SDK SPI is blocking, no flush needed
    return 0;
}
