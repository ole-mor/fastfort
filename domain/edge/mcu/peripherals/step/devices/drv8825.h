#ifndef DRV8825_H
#define DRV8825_H

#include "../step.h"

static inline step_t drv8825_default(void) {
    step_t s = {
        .identity = {
            .id           = "dd83a65b-db2a-4df4-a21c-abc123456804",
            .label        = "step_002",
            .manufacturer = "Texas Instruments",
            .model        = "DRV8825",
            .hw_revision  = "1.0",
            .location     = "",
            .installed    = "2026-03-02",
        },
        .config = {
            .steps_per_rev  = 200,
            .max_rpm        = 500,
            .accel_rate     = 500,
        },
        .data = {
            .current_pos    = 0,
            .target_pos     = 0,
            .is_moving      = 0,
            .status         = STEP_STATUS_UNKNOWN,
            .timestamp_ms   = 0,
        }
    };
    return s;
}

#endif // DRV8825_H
