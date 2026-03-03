#ifndef KY019_H
#define KY019_H

#include "../relay.h"

static inline relay_t ky019_default(void) {
    relay_t r = {
        .identity = {
            .id           = "bb83a65b-db2a-4df4-a21c-abc123456802",
            .label        = "relay_002",
            .manufacturer = "Generic",
            .model        = "KY-019 5V Relay",
            .hw_revision  = "1.0",
            .location     = "",
            .installed    = "2026-03-02",
        },
        .config = {
            .default_state  = 0,
            .pulse_width_ms = 500,
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

#endif // KY019_H
