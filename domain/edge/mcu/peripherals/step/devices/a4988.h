#ifndef A4988_H
#define A4988_H

#include "../step.h"

static inline step_t a4988_default(void) {
    step_t s = {
        .identity = {
            .id           = "j283a65b-db2a-4df4-a21c-abc123456791",
            .label        = "step_001",
            .manufacturer = "Allegro",
            .model        = "A4988",
            .hw_revision  = "1.0",
            .location     = "",
            .installed    = "2026-03-02",
        },
        .config = {
            .steps_per_rev  = 200,
            .max_rpm        = 300,
            .accel_rate     = 100,
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

#endif // A4988_H
