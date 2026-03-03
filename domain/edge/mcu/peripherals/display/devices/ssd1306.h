#ifndef SSD1306_H
#define SSD1306_H

#include "../display.h"

#define SSD1306_I2C_ADDR 0x3C
#define SSD1306_DEF_CONTRAST 0x7F

static inline display_t ssd1306_default(void) {
    display_t d = {
        .identity = {
            .id           = "f283a65b-db2a-4df4-a21c-abc123456781",
            .label        = "display_001",
            .manufacturer = "Solomon Systech",
            .model        = "SSD1306",
            .hw_revision  = "rev 1.0",
            .location     = "",
            .installed    = "2026-03-02",
        },
        .config = {
            .width      = 128,
            .height     = 64,
            .rotation   = 0,
            .brightness = SSD1306_DEF_CONTRAST,
        },
        .data = {
            .update_count = 0,
            .status       = DISPLAY_STATUS_UNKNOWN,
            .timestamp_ms = 0,
        }
    };
    return d;
}

#endif // SSD1306_H
