#include "nvm.h"
#include "stm32f4xx_hal.h"

#define FLASH_BASE_ADDR 0x08060000  // last sector, adjust per chip

void nvm_init(void) {
    HAL_Init();
}

void nvm_read(uint32_t offset, void *buf, size_t len) {
    uint8_t *src = (uint8_t *)(FLASH_BASE_ADDR + offset);
    uint8_t *dst = (uint8_t *)buf;
    for (size_t i = 0; i < len; i++)
        dst[i] = src[i];
}

void nvm_write(uint32_t offset, const void *buf, size_t len) {
    HAL_FLASH_Unlock();
    const uint8_t *src = (const uint8_t *)buf;
    for (size_t i = 0; i < len; i += 4)
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,
            FLASH_BASE_ADDR + offset + i,
            *(uint32_t *)(src + i));
    HAL_FLASH_Lock();
}

void nvm_erase(uint32_t offset, size_t len) {
    FLASH_EraseInitTypeDef erase = {
        .TypeErase    = FLASH_TYPEERASE_SECTORS,
        .Sector       = FLASH_SECTOR_11,
        .NbSectors    = 1,
        .VoltageRange = FLASH_VOLTAGE_RANGE_3
    };
    uint32_t error;
    HAL_FLASH_Unlock();
    HAL_FLASHEx_Erase(&erase, &error);
    HAL_FLASH_Lock();
}
