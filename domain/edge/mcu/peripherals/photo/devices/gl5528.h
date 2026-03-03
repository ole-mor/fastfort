#ifndef GL5528_H
#define GL5528_H

#include "../photo.h"

static inline photo_t gl5528_default(void) {
    photo_t p = {
        .identity = {
            .id           = "f883a65b-db2a-4df4-a21c-abc123456787",
            .label        = "photo_001",
            .manufacturer = "Generic",
            .model        = "GL5528",
            .hw_revision  = "1.0",
            .location     = "",
            .installed    = "2026-03-02",
        },
        .config = {
            .threshold_high     = 800,
            .threshold_low      = 200,
            .sample_interval_ms = 500,
            .pin                = 0,
            .addr               = 0,
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

#endif // GL5528_H
