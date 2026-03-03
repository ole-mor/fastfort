#ifndef BMP280_H
#define BMP280_H

#include "../pres.h"

#define BMP280_I2C_ADDR 0x76

static inline pres_t bmp280_default(void) {
    pres_t p = {
        .identity = {
            .id           = "g983a65b-db2a-4df4-a21c-abc123456788",
            .label        = "pres_001",
            .manufacturer = "Bosch Sensortec",
            .model        = "BMP280",
            .hw_revision  = "1.0",
            .location     = "",
            .installed    = "2026-03-02",
        },
        .config = {
            .warning_threshold_hpa = 1000.0f,
            .interval_ms           = 1000,
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

#endif // BMP280_H
