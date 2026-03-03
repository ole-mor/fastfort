#ifndef BTN_GENERIC_H
#define BTN_GENERIC_H

#include "../input.h"

static inline input_t btn_generic_default(void) {
    input_t i = {
        .identity = {
            .id           = "b483a65b-db2a-4df4-a21c-abc123456783",
            .label        = "btn_001",
            .manufacturer = "Generic",
            .model        = "Tactile Switch",
            .hw_revision  = "1.0",
            .location     = "",
            .installed    = "2026-03-02",
        },
        .config = {
            .debounce_ms = 50,
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

#endif // BTN_GENERIC_H
