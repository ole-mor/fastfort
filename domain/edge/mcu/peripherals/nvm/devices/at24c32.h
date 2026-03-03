#ifndef AT24C32_H
#define AT24C32_H

#include "../nvm.h"

#define AT24C32_I2C_ADDR 0x50

static inline nvm_t at24c32_default(void) {
    nvm_t n = {
        .identity = {
            .id           = "e783a65b-db2a-4df4-a21c-abc123456786",
            .label        = "nvm_001",
            .manufacturer = "Microchip",
            .model        = "AT24C32",
            .hw_revision  = "A",
            .location     = "",
            .installed    = "2026-03-02",
        },
        .config = {
            .base_address   = 0x0000,
            .capacity_bytes = 4096,
            .page_size      = 32,
        },
        .data = {
            .write_count  = 0,
            .free_bytes   = 4096,
            .status       = NVM_STATUS_UNKNOWN,
            .timestamp_ms = 0,
        }
    };
    return n;
}

#endif // AT24C32_H
