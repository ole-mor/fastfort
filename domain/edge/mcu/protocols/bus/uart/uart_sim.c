#include "uart.h"
#include <stdio.h>
#include <string.h>

#define UART_SIM_MAX_BUSES  3
#define UART_SIM_BUF_SIZE   256

static uint8_t  sim_initialized[UART_SIM_MAX_BUSES] = {0};
static uint32_t sim_baudrate[UART_SIM_MAX_BUSES]     = {0};
static uint8_t  sim_rx_buf[UART_SIM_MAX_BUSES][UART_SIM_BUF_SIZE];
static uint16_t sim_rx_len[UART_SIM_MAX_BUSES]       = {0};

static int8_t check_bus(const char* fn, uint8_t bus_id) {
    if (bus_id >= UART_SIM_MAX_BUSES) {
        printf("[UART SIM] %s: invalid bus_id %u\n", fn, bus_id);
        return -1;
    }
    return 0;
}

// --- public sim helper: inject bytes into rx buffer ---
void uart_sim_inject(uint8_t bus_id, const uint8_t* data, uint16_t len) {
    if (bus_id >= UART_SIM_MAX_BUSES) return;
    uint16_t copy = len < UART_SIM_BUF_SIZE ? len : UART_SIM_BUF_SIZE;
    memcpy(sim_rx_buf[bus_id], data, copy);
    sim_rx_len[bus_id] = copy;
}

// --- hal implementation ---

int8_t uart_init(uint8_t bus_id, uint32_t baudrate) {
    if (check_bus("uart_init", bus_id) != 0) return -1;
    sim_initialized[bus_id] = 1;
    sim_baudrate[bus_id]     = baudrate;
    sim_rx_len[bus_id]       = 0;
    printf("[UART SIM] bus %u init  baudrate=%u\n", bus_id, baudrate);
    return 0;
}

int8_t uart_deinit(uint8_t bus_id) {
    if (check_bus("uart_deinit", bus_id) != 0) return -1;
    sim_initialized[bus_id] = 0;
    sim_baudrate[bus_id]     = 0;
    sim_rx_len[bus_id]       = 0;
    printf("[UART SIM] bus %u deinit\n", bus_id);
    return 0;
}

int8_t uart_write(uint8_t bus_id, const uint8_t* data, uint16_t len) {
    if (check_bus("uart_write", bus_id) != 0) return -1;
    if (!sim_initialized[bus_id]) {
        printf("[UART SIM] bus %u write: not initialized\n", bus_id);
        return -1;
    }
    printf("[UART SIM] bus %u write  len=%-4u  bytes=", bus_id, len);
    for (uint16_t i = 0; i < len; i++) printf("%02X ", data[i]);
    printf("\n");
    return 0;
}

int16_t uart_read(uint8_t bus_id, uint8_t* buffer, uint16_t max_len) {
    if (check_bus("uart_read", bus_id) != 0) return -1;
    if (!sim_initialized[bus_id]) {
        printf("[UART SIM] bus %u read: not initialized\n", bus_id);
        return -1;
    }
    uint16_t n = sim_rx_len[bus_id] < max_len ? sim_rx_len[bus_id] : max_len;
    memcpy(buffer, sim_rx_buf[bus_id], n);
    sim_rx_len[bus_id] = 0;
    printf("[UART SIM] bus %u read   len=%-4u  bytes=", bus_id, n);
    for (uint16_t i = 0; i < n; i++) printf("%02X ", buffer[i]);
    printf("\n");
    return n;
}

int16_t uart_available(uint8_t bus_id) {
    if (check_bus("uart_available", bus_id) != 0) return -1;
    printf("[UART SIM] bus %u available  bytes=%u\n", bus_id, sim_rx_len[bus_id]);
    return sim_rx_len[bus_id];
}

int8_t uart_flush(uint8_t bus_id) {
    if (check_bus("uart_flush", bus_id) != 0) return -1;
    printf("[UART SIM] bus %u flush\n", bus_id);
    return 0;
}
