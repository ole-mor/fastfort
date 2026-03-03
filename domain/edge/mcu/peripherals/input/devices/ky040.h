#ifndef KY040_H
#define KY040_H

#include "../input.h"

static inline input_t ky040_default(void) {
    input_t i = {
        .identity = {
            .id           = "5583a65b-db2a-4df4-a21c-abc123456796",
            .label        = "input_002",
            .manufacturer = "Generic",
            .model        = "KY-040 Rotary Encoder",
            .hw_revision  = "1.0",
            .location     = "",
            .installed    = "2026-03-02",
        },
        .config = {
            .debounce_ms = 10,
            .active_low  = 1,
        },
        .data = {
            .state        = 0,
            .status       = INPUT_STATUS_UNKNOWN,
            .timestamp_ms = 0,
        }
    };
    return i;
}

#endif // KY040_H
