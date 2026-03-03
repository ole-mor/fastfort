#ifndef SRD_05VDC_H
#define SRD_05VDC_H

#include "../relay.h"

static inline relay_t srd_05vdc_default(void) {
    relay_t r = {
        .identity = {
            .id           = "h083a65b-db2a-4df4-a21c-abc123456789",
            .label        = "relay_001",
            .manufacturer = "Songle",
            .model        = "SRD-05VDC",
            .hw_revision  = "1.0",
            .location     = "",
            .installed    = "2026-03-02",
        },
        .config = {
            .default_state  = 0,
            .pulse_width_ms = 1000,
        },
        .data = {
            .current_state  = 0,
            .toggle_count   = 0,
            .status         = RELAY_STATUS_UNKNOWN,
            .timestamp_ms   = 0,
        }
    };
    return r;
}

#endif // SRD_05VDC_H
