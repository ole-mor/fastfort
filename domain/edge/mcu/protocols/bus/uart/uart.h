#ifndef UART_H
#define UART_H

#include <stdint.h>

int8_t uart_init(uint8_t bus_id, uint32_t baudrate);
int8_t uart_write(uint8_t bus_id, const uint8_t* data, uint16_t len);
int16_t uart_read(uint8_t bus_id, uint8_t* buffer, uint16_t max_len);

#endif
