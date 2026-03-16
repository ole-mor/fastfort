#include "./uart.h"
#include <stdio.h>

int8_t uart_init(uint8_t bus_id, uint32_t baudrate) {
    printf("[SIM] UART Init Bus: %u, Baudrate: %u\n", bus_id, baudrate);
    return 0;
}

int8_t uart_deinit(uint8_t bus_id){
    printf("[SIM] UART Deinit Bus: %u\n", bus_id);
    return 0;
}

int8_t uart_write(uint8_t bus_id, const uint8_t* data, uint16_t len) {
    printf("[SIM] UART Write Bus: %u, Len: %u, Data: ", bus_id, len);
    for (uint16_t i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
    return 0;
}

int16_t uart_read(uint8_t bus_id, uint8_t* buffer, uint16_t max_len) {
    printf("[SIM] UART Read Bus: %u, Max Len: %u\n", bus_id, max_len);
    return 0;
}

int16_t uart_available(uint8_t bus_id){
    printf("[SIM] UART Check Available Bus: %u\n", bus_id);
    return 0;
}

int8_t uart_flush(uint8_t bus_id){
    printf("[SIM] UART Flush Bus: %u\n", bus_id);
    return 0;
}


