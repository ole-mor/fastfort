#ifndef BNO055_H
#define BNO055_H

#include "../imu.h"

#define BNO055_I2C_ADDR 0x28

static inline imu_t bno055_default(void) {
    imu_t i = {
        .identity = {
            .id           = "4483a65b-db2a-4df4-a21c-abc123456795",
            .label        = "imu_002",
            .manufacturer = "Bosch Sensortec",
            .model        = "BNO055",
            .hw_revision  = "1.0",
            .location     = "",
            .installed    = "2026-03-02",
        },
        .config = {
            .accel_range_g   = 4,
            .gyro_range_dps  = 2000,
            .interval_ms     = 100,
        },
        .data = {
            .accel_x      = 0,
            .accel_y      = 0,
            .accel_z      = 0,
            .gyro_x       = 0,
            .gyro_y       = 0,
            .gyro_z       = 0,
            .status       = IMU_STATUS_UNKNOWN,
            .timestamp_ms = 0,
        }
    };
    return i;
}

#endif // BNO055_H
