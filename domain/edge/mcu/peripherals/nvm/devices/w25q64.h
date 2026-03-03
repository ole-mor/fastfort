#ifndef W25Q64_H
#define W25Q64_H

#include "../nvm.h"

static inline nvm_t w25q64_default(void) {
    nvm_t n = {
        .identity = {
            .id           = "8883a65b-db2a-4df4-a21c-abc123456799",
            .label        = "nvm_002",
            .manufacturer = "Winbond",
            .model        = "W25Q64",
            .hw_revision  = "1.0",
            .location     = "",
            .installed    = "2026-03-02",
        },
        .config = {
            .base_address   = 0x000000,
            .capacity_bytes = 8388608, // 8MB
            .page_size      = 256,
        },
        .data = {
            .write_count  = 0,
            .free_bytes   = 8388608,
            .status       = NVM_STATUS_UNKNOWN,
            .timestamp_ms = 0,
        }
    };
    return n;
}

#endif // W25Q64_H
