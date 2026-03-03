#ifndef TB6612_H
#define TB6612_H

#include "../motor.h"

static inline motor_t tb6612_default(void) {
    motor_t m = {
        .identity = {
            .id           = "7783a65b-db2a-4df4-a21c-abc123456798",
            .label        = "motor_002",
            .manufacturer = "Toshiba",
            .model        = "TB6612FNG",
            .hw_revision  = "1.0",
            .location     = "",
            .installed    = "2026-03-02",
        },
        .config = {
            .max_speed_rpm    = 5000,
            .invert_direction = 0,
        },
        .data = {
            .current_speed_rpm = 0,
            .status            = MOTOR_STATUS_UNKNOWN,
            .timestamp_ms      = 0,
        }
    };
    return m;
}

#endif // TB6612_H
