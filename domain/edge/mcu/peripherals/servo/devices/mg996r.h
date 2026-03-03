#ifndef MG996R_H
#define MG996R_H

#include "../servo.h"

#define MG996R_MIN_PULSE_US 500
#define MG996R_MAX_PULSE_US 2500
#define MG996R_MAX_ANGLE    180

static inline servo_t mg996r_default(void) {
    servo_t s = {
        .identity = {
            .id           = "cc83a65b-db2a-4df4-a21c-abc123456803",
            .label        = "servo_002",
            .manufacturer = "TowerPro",
            .model        = "MG996R",
            .hw_revision  = "1.0",
            .location     = "",
            .installed    = "2026-03-02",
        },
        .config = {
            .min_pulse_us  = MG996R_MIN_PULSE_US,
            .max_pulse_us  = MG996R_MAX_PULSE_US,
            .max_angle_deg = MG996R_MAX_ANGLE,
        },
        .data = {
            .current_angle_deg = 0,
            .target_angle_deg  = 0,
            .status            = SERVO_STATUS_UNKNOWN,
            .timestamp_ms      = 0,
        }
    };
    return s;
}

#endif // MG996R_H
