#include "uart.h"
#include "hardware/uart.h"

static uart_inst_t* buses[] = {uart0, uart1};

int8_t uart_init(uint8_t bus_id, uint32_t baudrate) {
    uart_init(buses[bus_id], baudrate);
    return 0;
}

int8_t uart_deinit(uint8_t bus_id) {
    uart_deinit(buses[bus_id]);
    return 0;
}

int8_t uart_write(uint8_t bus_id, const uint8_t* data, uint16_t len) {
    uart_write_blocking(buses[bus_id], data, len);
    return 0;
}

int16_t uart_read(uint8_t bus_id, uint8_t* buffer, uint16_t max_len) {
    uart_read_blocking(buses[bus_id], buffer, max_len);
    return max_len;
}

int16_t uart_available(uint8_t bus_id) {
    return uart_is_readable(buses[bus_id]) ? 1 : 0;
}

int8_t uart_flush(uint8_t bus_id) {
    uart_tx_wait_blocking(buses[bus_id]);
    return 0;
}
