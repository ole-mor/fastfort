#ifndef MS5611_H
#define MS5611_H

#include "../pres.h"

#define MS5611_I2C_ADDR 0x77

static inline pres_t ms5611_default(void) {
    pres_t p = {
        .identity = {
            .id           = "aa83a65b-db2a-4df4-a21c-abc123456801",
            .label        = "pres_002",
            .manufacturer = "TE Connectivity",
            .model        = "MS5611",
            .hw_revision  = "1.0",
            .location     = "",
            .installed    = "2026-03-02",
        },
        .config = {
            .warning_threshold_hpa = 1013.25f,
            .interval_ms           = 500,
        },
        .data = {
            .pressure_hpa  = 0.0f,
            .temperature_c = 0.0f,
            .status        = PRES_STATUS_UNKNOWN,
            .timestamp_ms  = 0,
        }
    };
    return p;
}

#endif // MS5611_H
