#include "uart.h"
#include "driver/uart.h"

int8_t uart_init(uint8_t bus_id, uint32_t baudrate){
    uart_config_h config = {
        .baud_rate  = baudrate,
        .data_bits  = UART_DATA_8_BITS,
        .parity     = UART_PARITY_DISABLE,
        .stop_bits  = UART_STOP_BITS_1,
        .flow_ctrl  = UART_HW_FLOWCTRL_DISABLE,
    };
    uart_param_config(bus_id, &config);
    uart_driver_install(bus_id, 256, 256, 0, NULL, 0);
    return 0;
}

int8_t uart_deinit(uint8_t bus_id){
    uart_driver_delete(bus_id);
    return 0;
}

int8_t uart_write(uint8_t bus_id, const uint8_t* data, uint16_t len){
    uart_write_bytes(bus_id, (const char*)data, len);
    return 0;
}

int16_t uart_read(uint8_t bus_id, uint8_t* buffer, uint16_t max_len){
    return uart_read_bytes(bus_id, buffer, max_len, pdMS_TO_TICKS(100));
}

int16_t uart_available(uint8_t bus_id){
    size_t len = 0;
    uart_get_buffered_data_len(bus_id, &len);
    return (int16_t)len;
}

int8_t uart_flush(uint8_t bus_id){
    uart_flush(bus_id);
    return 0;
}

