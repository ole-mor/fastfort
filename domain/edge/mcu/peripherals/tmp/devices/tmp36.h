#ifndef TMP36_H
#define TMP36_H

// Reference Image: https://www.google.com/search?tbm=isch&q=TMP36+sensor
#include "../tmp.h"

static inline tmp_t tmp36_default(void) {
    tmp_t t = {
        .identity = {
            .id           = "1183a65b-db2a-4df4-a21c-abc123456792", 
            .label        = "tmp36_001",                               
            .manufacturer = "Analog Devices",
            .model        = "TMP36",
            .hw_revision  = "1.0",
            .location     = "",                                   
            .installed    = "2026-03-02",                      
        },
        .config = {
            .alert_low   = -40.0f,
            .alert_high  = 125.0f,
            .interval_ms = 1000,
            .pin         = 0, // Default ADC pin 
            .addr        = 0, // Unused
        },
        .data = {
            .raw          = 0,
            .status       = TMP_STATUS_UNKNOWN,
            .timestamp_ms = 0,
        }
    };
    return t;
}

#endif // TMP36_H
