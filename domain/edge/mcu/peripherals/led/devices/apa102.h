#ifndef APA102_H
#define APA102_H

#include "../led.h"

static inline led_t apa102_default(void) {
    led_t l = {
        .identity = {
            .id           = "6683a65b-db2a-4df4-a21c-abc123456797",
            .label        = "led_002",
            .manufacturer = "Neonode",
            .model        = "APA102 DotStar",
            .hw_revision  = "1.0",
            .location     = "",
            .installed    = "2026-03-02",
        },
        .config = {
            .blink_interval_ms = 0,
            .default_brightness = 31,
        },
        .data = {
            .state        = 0,
            .brightness   = 31,
            .status       = LED_STATUS_UNKNOWN,
            .timestamp_ms = 0,
        }
    };
    return l;
}

#endif // APA102_H
