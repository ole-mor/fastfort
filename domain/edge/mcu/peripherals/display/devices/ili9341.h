#ifndef ILI9341_H
#define ILI9341_H

#include "../display.h"

static inline display_t ili9341_default(void) {
    display_t d = {
        .identity = {
            .id           = "3383a65b-db2a-4df4-a21c-abc123456794",
            .label        = "display_002",
            .manufacturer = "Ilitek",
            .model        = "ILI9341",
            .hw_revision  = "1.0",
            .location     = "",
            .installed    = "2026-03-02",
        },
        .config = {
            .width      = 240,
            .height     = 320,
            .rotation   = 0,
            .brightness = 255,
        },
        .data = {
            .update_count = 0,
            .status       = DISPLAY_STATUS_UNKNOWN,
            .timestamp_ms = 0,
        }
    };
    return d;
}

#endif // ILI9341_H
