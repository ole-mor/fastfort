#ifndef MPU6050_H
#define MPU6050_H

#include "../imu.h"

#define MPU6050_I2C_ADDR 0x68
#define MPU6050_DEF_ACCEL 2
#define MPU6050_DEF_GYRO  250

static inline imu_t mpu6050_default(void) {
    imu_t i = {
        .identity = {
            .id           = "a383a65b-db2a-4df4-a21c-abc123456782",
            .label        = "imu_001",
            .manufacturer = "InvenSense",
            .model        = "MPU-6050",
            .hw_revision  = "rev C",
            .location     = "",
            .installed    = "2026-03-02",
        },
        .config = {
            .accel_range_g   = MPU6050_DEF_ACCEL,
            .gyro_range_dps  = MPU6050_DEF_GYRO,
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

#endif // MPU6050_H
