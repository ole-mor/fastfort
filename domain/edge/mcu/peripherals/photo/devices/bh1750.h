#ifndef BH1750_H
#define BH1750_H

#include "../photo.h"

#define BH1750_I2C_ADDR 0x23

static inline photo_t bh1750_default(void) {
    photo_t p = {
        .identity = {
            .id           = "9983a65b-db2a-4df4-a21c-abc123456800",
            .label        = "photo_002",
            .manufacturer = "ROHM",
            .model        = "BH1750",
            .hw_revision  = "1.0",
            .location     = "",
            .installed    = "2026-03-02",
        },
        .config = {
            .threshold_high     = 1000,
            .threshold_low      = 100,
            .sample_interval_ms = 1000,
            .pin                = 0,
            .addr               = BH1750_I2C_ADDR,
        },
        .data = {
            .raw_value    = 0,
            .lux_estimate = 0,
            .status       = PHOTO_STATUS_UNKNOWN,
            .timestamp_ms = 0,
        }
    };
    return p;
}

#endif // BH1750_H
