#include "uart.h"
#include "stm32f4xx_hal.h"

static UART_HandleTypeDef* buses[3];  // populated at init

int8_t uart_init(uint8_t bus_id, uint32_t baudrate) {
    buses[bus_id]->Init.BaudRate     = baudrate;
    buses[bus_id]->Init.WordLength   = UART_WORDLENGTH_8B;
    buses[bus_id]->Init.StopBits     = UART_STOPBITS_1;
    buses[bus_id]->Init.Parity       = UART_PARITY_NONE;
    buses[bus_id]->Init.Mode         = UART_MODE_TX_RX;
    buses[bus_id]->Init.HwFlowCtl   = UART_HWCONTROL_NONE;
    HAL_UART_Init(buses[bus_id]);
    return 0;
}

int8_t uart_deinit(uint8_t bus_id) {
    HAL_UART_DeInit(buses[bus_id]);
    return 0;
}

int8_t uart_write(uint8_t bus_id, const uint8_t* data, uint16_t len) {
    HAL_UART_Transmit(buses[bus_id], data, len, HAL_MAX_DELAY);
    return 0;
}

int16_t uart_read(uint8_t bus_id, uint8_t* buffer, uint16_t max_len) {
    HAL_UART_Receive(buses[bus_id], buffer, max_len, HAL_MAX_DELAY);
    return max_len;
}

int16_t uart_available(uint8_t bus_id) {
    return __HAL_UART_GET_FLAG(buses[bus_id], UART_FLAG_RXNE) ? 1 : 0;
}

int8_t uart_flush(uint8_t bus_id) {
    while (__HAL_UART_GET_FLAG(buses[bus_id], UART_FLAG_TC) == RESET);
    return 0;
}
