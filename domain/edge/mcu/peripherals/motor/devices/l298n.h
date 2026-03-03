#ifndef L298N_H
#define L298N_H

#include "../motor.h"

static inline motor_t l298n_default(void) {
    motor_t m = {
        .identity = {
            .id           = "d683a65b-db2a-4df4-a21c-abc123456785",
            .label        = "motor_001",
            .manufacturer = "STMicroelectronics",
            .model        = "L298N",
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

#endif // L298N_H
