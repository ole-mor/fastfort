#include "i2c.h"
#include "stm32f4xx_hal.h"

extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

static I2C_HandleTypeDef* buses[] = {&hi2c1, &hi2c2};

int8_t i2c_init(uint8_t bus_id, uint32_t baudrate) {
    // HAL init handled by generated code (MX_I2Cx_Init)
    HAL_I2C_Init(buses[bus_id]);
    return 0;
}

int8_t i2c_deinit(uint8_t bus_id) {
    HAL_I2C_DeInit(buses[bus_id]);
    return 0;
}

int8_t i2c_write(uint8_t bus_id, uint8_t addr, const uint8_t* data, uint16_t len) {
    HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(buses[bus_id], addr << 1, (uint8_t*)data, len, HAL_MAX_DELAY);
    return status == HAL_OK ? 0 : -1;
}

int16_t i2c_read(uint8_t bus_id, uint8_t addr, uint8_t* buf, uint16_t len) {
    HAL_StatusTypeDef status = HAL_I2C_Master_Receive(buses[bus_id], addr << 1, buf, len, HAL_MAX_DELAY);
    return status == HAL_OK ? len : -1;
}

int8_t i2c_write_reg(uint8_t bus_id, uint8_t addr, uint8_t reg, uint8_t value) {
    HAL_StatusTypeDef status = HAL_I2C_Mem_Write(buses[bus_id], addr << 1, reg, I2C_MEMADD_SIZE_8BIT, &value, 1, HAL_MAX_DELAY);
    return status == HAL_OK ? 0 : -1;
}

int8_t i2c_read_reg(uint8_t bus_id, uint8_t addr, uint8_t reg, uint8_t* value) {
    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(buses[bus_id], addr << 1, reg, I2C_MEMADD_SIZE_8BIT, value, 1, HAL_MAX_DELAY);
    return status == HAL_OK ? 0 : -1;
}

int8_t i2c_flush(uint8_t bus_id) {
    // STM32 HAL I2C is blocking, no flush needed
    return 0;
}
