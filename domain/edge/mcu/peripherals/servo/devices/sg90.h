#ifndef SG90_H
#define SG90_H

#include "../servo.h"

#define SG90_MIN_PULSE_US 500
#define SG90_MAX_PULSE_US 2400
#define SG90_MAX_ANGLE    180

static inline servo_t sg90_default(void) {
    servo_t s = {
        .identity = {
            .id           = "i183a65b-db2a-4df4-a21c-abc123456790",
            .label        = "servo_001",
            .manufacturer = "TowerPro",
            .model        = "SG90",
            .hw_revision  = "1.0",
            .location     = "",
            .installed    = "2026-03-02",
        },
        .config = {
            .min_pulse_us  = SG90_MIN_PULSE_US,
            .max_pulse_us  = SG90_MAX_PULSE_US,
            .max_angle_deg = SG90_MAX_ANGLE,
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

#endif // SG90_H
