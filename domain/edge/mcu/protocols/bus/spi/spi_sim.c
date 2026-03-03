#include "./spi.h"
#include <stddef.h>
#include <stdio.h>

int8_t spi_init(uint8_t bus_id, uint32_t frequency, uint8_t mode) {
    printf("[SIM] SPI Init Bus: %u, Freq: %u, Mode: %u\n", bus_id, frequency, mode);
    return 0;
}

int8_t spi_transfer(uint8_t bus_id, uint8_t cs_pin, const uint8_t* tx_data, uint8_t* rx_data, uint16_t len) {
    printf("[SIM] SPI Transfer Bus: %u, CS: %u, Len: %u, TX: ", bus_id, cs_pin, len);
    for (uint16_t i = 0; i < len; i++) {
        printf("%02X ", tx_data[i]);
    }
    printf("\n");
    if (rx_data != NULL) {
        for (uint16_t i = 0; i < len; i++) {
            rx_data[i] = 0x00;
        }
    }
    return 0;
}

int8_t spi_write(uint8_t bus_id, uint8_t cs_pin, const uint8_t* data, uint16_t len) {
    printf("[SIM] SPI Write Bus: %u, CS: %u, Len: %u, Data: ", bus_id, cs_pin, len);
    for (uint16_t i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
    return 0;
}

int8_t spi_read(uint8_t bus_id, uint8_t cs_pin, uint8_t* data, uint16_t len) {
    printf("[SIM] SPI Read Bus: %u, CS: %u, Len: %u\n", bus_id, cs_pin, len);
    for (uint16_t i = 0; i < len; i++) {
        data[i] = 0x00;
    }
    return 0;
}
