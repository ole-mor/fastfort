#include "spi.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"

static spi_device_handle_t spi_handles[3] = {NULL};

int8_t spi_init(uint8_t bus_id, uint32_t baudrate) {
    spi_bus_config_t bus_cfg = {
        .mosi_io_num   = 23,
        .miso_io_num   = 19,
        .sclk_io_num   = 18,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
    };
    spi_bus_initialize(bus_id + 1, &bus_cfg, SPI_DMA_CH_AUTO);
    return 0;
}

int8_t spi_deinit(uint8_t bus_id) {
    if (spi_handles[bus_id]) {
        spi_bus_remove_device(spi_handles[bus_id]);
        spi_handles[bus_id] = NULL;
    }
    spi_bus_free(bus_id + 1);
    return 0;
}

int8_t spi_select(uint8_t bus_id, uint8_t cs_pin) {
    gpio_set_level(cs_pin, 0);
    return 0;
}

int8_t spi_deselect(uint8_t bus_id, uint8_t cs_pin) {
    gpio_set_level(cs_pin, 1);
    return 0;
}

int8_t spi_write(uint8_t bus_id, const uint8_t* data, uint16_t len) {
    spi_transaction_t t = {
        .length    = len * 8,
        .tx_buffer = data,
    };
    spi_device_transmit(spi_handles[bus_id], &t);
    return 0;
}

int16_t spi_read(uint8_t bus_id, uint8_t* buf, uint16_t len) {
    spi_transaction_t t = {
        .length    = len * 8,
        .rx_buffer = buf,
    };
    spi_device_transmit(spi_handles[bus_id], &t);
    return len;
}

int8_t spi_transfer(uint8_t bus_id, const uint8_t* tx, uint8_t* rx, uint16_t len) {
    spi_transaction_t t = {
        .length    = len * 8,
        .tx_buffer = tx,
        .rx_buffer = rx,
    };
    spi_device_transmit(spi_handles[bus_id], &t);
    return 0;
}

int8_t spi_flush(uint8_t bus_id) {
    // ESP-IDF SPI transactions are synchronous
    return 0;
}
