#ifndef WS2812_H
#define WS2812_H

#include "../led.h"

static inline led_t ws2812_default(void) {
    led_t l = {
        .identity = {
            .id           = "c583a65b-db2a-4df4-a21c-abc123456784",
            .label        = "led_001",
            .manufacturer = "Worldsemi",
            .model        = "WS2812B",
            .hw_revision  = "v5",
            .location     = "",
            .installed    = "2026-03-02",
        },
        .config = {
            .blink_interval_ms = 0,
            .default_brightness = 100,
        },
        .data = {
            .state        = 0,
            .brightness   = 100,
            .status       = LED_STATUS_UNKNOWN,
            .timestamp_ms = 0,
        }
    };
    return l;
}

#endif // WS2812_H
