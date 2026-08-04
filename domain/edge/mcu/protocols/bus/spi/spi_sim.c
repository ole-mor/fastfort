#include "spi.h"
#include <stdio.h>
#include <string.h>

#define SPI_SIM_MAX_BUSES  2
#define SPI_SIM_BUF_SIZE   256

static uint8_t  sim_initialized[SPI_SIM_MAX_BUSES] = {0};
static uint32_t sim_baudrate[SPI_SIM_MAX_BUSES]     = {0};
static int8_t   sim_cs_pin[SPI_SIM_MAX_BUSES];           // currently selected cs pin, -1 = none
static uint8_t  sim_rx_buf[SPI_SIM_MAX_BUSES][SPI_SIM_BUF_SIZE];
static uint16_t sim_rx_len[SPI_SIM_MAX_BUSES]       = {0};

static int8_t check_bus(const char* fn, uint8_t bus_id) {
    if (bus_id >= SPI_SIM_MAX_BUSES) {
        printf("[SPI SIM] %s: invalid bus_id %u\n", fn, bus_id);
        return -1;
    }
    return 0;
}

// --- public sim helper: inject bytes to return on next read/transfer ---
void spi_sim_inject(uint8_t bus_id, const uint8_t* data, uint16_t len) {
    if (bus_id >= SPI_SIM_MAX_BUSES) return;
    uint16_t copy = len < SPI_SIM_BUF_SIZE ? len : SPI_SIM_BUF_SIZE;
    memcpy(sim_rx_buf[bus_id], data, copy);
    sim_rx_len[bus_id] = copy;
}

// --- hal implementation ---

int8_t spi_init(uint8_t bus_id, uint32_t baudrate) {
    if (check_bus("spi_init", bus_id) != 0) return -1;
    sim_initialized[bus_id] = 1;
    sim_baudrate[bus_id]     = baudrate;
    sim_cs_pin[bus_id]       = -1;
    sim_rx_len[bus_id]       = 0;
    printf("[SPI SIM] bus %u init  baudrate=%u\n", bus_id, baudrate);
    return 0;
}

int8_t spi_deinit(uint8_t bus_id) {
    if (check_bus("spi_deinit", bus_id) != 0) return -1;
    sim_initialized[bus_id] = 0;
    sim_cs_pin[bus_id]       = -1;
    printf("[SPI SIM] bus %u deinit\n", bus_id);
    return 0;
}

int8_t spi_select(uint8_t bus_id, uint8_t cs_pin) {
    if (check_bus("spi_select", bus_id) != 0) return -1;
    sim_cs_pin[bus_id] = cs_pin;
    printf("[SPI SIM] bus %u select    cs_pin=%u\n", bus_id, cs_pin);
    return 0;
}

int8_t spi_deselect(uint8_t bus_id, uint8_t cs_pin) {
    if (check_bus("spi_deselect", bus_id) != 0) return -1;
    sim_cs_pin[bus_id] = -1;
    printf("[SPI SIM] bus %u deselect  cs_pin=%u\n", bus_id, cs_pin);
    return 0;
}

int8_t spi_write(uint8_t bus_id, const uint8_t* data, uint16_t len) {
    if (check_bus("spi_write", bus_id) != 0) return -1;
    if (sim_cs_pin[bus_id] < 0) {
        printf("[SPI SIM] bus %u write: no device selected\n", bus_id);
        return -1;
    }
    printf("[SPI SIM] bus %u write  cs=%d  len=%-4u  bytes=", bus_id, sim_cs_pin[bus_id], len);
    for (uint16_t i = 0; i < len; i++) printf("%02X ", data[i]);
    printf("\n");
    return 0;
}

int16_t spi_read(uint8_t bus_id, uint8_t* buf, uint16_t len) {
    if (check_bus("spi_read", bus_id) != 0) return -1;
    if (sim_cs_pin[bus_id] < 0) {
        printf("[SPI SIM] bus %u read: no device selected\n", bus_id);
        return -1;
    }
    uint16_t n = sim_rx_len[bus_id] < len ? sim_rx_len[bus_id] : len;
    memcpy(buf, sim_rx_buf[bus_id], n);
    memset(buf + n, 0x00, len - n);   // pad remainder with 0x00
    sim_rx_len[bus_id] = 0;
    printf("[SPI SIM] bus %u read   cs=%d  len=%-4u  bytes=", bus_id, sim_cs_pin[bus_id], len);
    for (uint16_t i = 0; i < len; i++) printf("%02X ", buf[i]);
    printf("\n");
    return len;
}

int8_t spi_transfer(uint8_t bus_id, const uint8_t* tx, uint8_t* rx, uint16_t len) {
    if (check_bus("spi_transfer", bus_id) != 0) return -1;
    if (sim_cs_pin[bus_id] < 0) {
        printf("[SPI SIM] bus %u transfer: no device selected\n", bus_id);
        return -1;
    }
    uint16_t n = sim_rx_len[bus_id] < len ? sim_rx_len[bus_id] : len;
    memcpy(rx, sim_rx_buf[bus_id], n);
    memset(rx + n, 0x00, len - n);
    sim_rx_len[bus_id] = 0;
    printf("[SPI SIM] bus %u transfer  cs=%d  len=%-4u\n", bus_id, sim_cs_pin[bus_id], len);
    printf("           TX: ");
    for (uint16_t i = 0; i < len; i++) printf("%02X ", tx[i]);
    printf("\n           RX: ");
    for (uint16_t i = 0; i < len; i++) printf("%02X ", rx[i]);
    printf("\n");
    return 0;
}

int8_t spi_flush(uint8_t bus_id) {
    if (check_bus("spi_flush", bus_id) != 0) return -1;
    printf("[SPI SIM] bus %u flush\n", bus_id);
    return 0;
}
