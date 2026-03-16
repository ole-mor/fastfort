#include "spi.h"
#include "stm32f4xx_hal.h"

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;

static SPI_HandleTypeDef* buses[] = {&hspi1, &hspi2};

int8_t spi_init(uint8_t bus_id, uint32_t baudrate) {
    // HAL init handled by generated code (MX_SPIx_Init)
    HAL_SPI_Init(buses[bus_id]);
    return 0;
}

int8_t spi_deinit(uint8_t bus_id) {
    HAL_SPI_DeInit(buses[bus_id]);
    return 0;
}

int8_t spi_select(uint8_t bus_id, uint8_t cs_pin) {
    // cs_pin maps to a GPIO pin — pull low to select
    HAL_GPIO_WritePin(GPIOA, cs_pin, GPIO_PIN_RESET);
    return 0;
}

int8_t spi_deselect(uint8_t bus_id, uint8_t cs_pin) {
    HAL_GPIO_WritePin(GPIOA, cs_pin, GPIO_PIN_SET);
    return 0;
}

int8_t spi_write(uint8_t bus_id, const uint8_t* data, uint16_t len) {
    HAL_StatusTypeDef status = HAL_SPI_Transmit(buses[bus_id], (uint8_t*)data, len, HAL_MAX_DELAY);
    return status == HAL_OK ? 0 : -1;
}

int16_t spi_read(uint8_t bus_id, uint8_t* buf, uint16_t len) {
    HAL_StatusTypeDef status = HAL_SPI_Receive(buses[bus_id], buf, len, HAL_MAX_DELAY);
    return status == HAL_OK ? len : -1;
}

int8_t spi_transfer(uint8_t bus_id, const uint8_t* tx, uint8_t* rx, uint16_t len) {
    HAL_StatusTypeDef status = HAL_SPI_TransmitReceive(buses[bus_id], (uint8_t*)tx, rx, len, HAL_MAX_DELAY);
    return status == HAL_OK ? 0 : -1;
}

int8_t spi_flush(uint8_t bus_id) {
    while (__HAL_SPI_GET_FLAG(buses[bus_id], SPI_FLAG_BSY));
    return 0;
}
