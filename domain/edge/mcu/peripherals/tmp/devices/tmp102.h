#ifndef TMP102_H
#define TMP102_H

#include "../tmp.h"

#define TMP102_ADDR     0x48
#define TMP102_RESOLUTION 0.0625f
#define TMP102_RANGE_LOW  -40.0f 
#define TMP102_RANGE_HIGH  125.0f 

static inline tmp_t tmp102_default(void) {
    tmp_t t = {
        .identity = {
            .id           = "793e5360-b44d-4998-8566-0c19575dd6b1", 
            .label        = "tmp102_001",                               
            .manufacturer = "Texas Instruments",
            .model        = "TMP102",
            .hw_revision  = "rev A",
            .location     = "",                                   
            .installed    = "2026-03-02",                      
        },
        .config = {
            .alert_low   = TMP102_RANGE_LOW,
            .alert_high  = TMP102_RANGE_HIGH,
            .interval_ms = 1000, // reads every second
            .pin         = 0,    // Unused
            .addr        = TMP102_ADDR,
        },
        .data = {
            .raw          = 0,
            .status       = TMP_STATUS_UNKNOWN,
            .timestamp_ms = 0,
        }
    };
    return t;
}

#endif // TMP102_H
