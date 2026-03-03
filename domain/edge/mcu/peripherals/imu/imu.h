#ifndef IMU_H
#define IMU_H

#include <stdint.h>
#include "../pe.h"

typedef enum {
    IMU_STATUS_OK,
    IMU_STATUS_STALE,
    IMU_STATUS_CALIBRATING,
    IMU_STATUS_FAULT,
    IMU_STATUS_UNKNOWN
} imu_status_t;

typedef struct {
    uint8_t accel_range_g;
    uint16_t gyro_range_dps;
    uint32_t interval_ms;
    uint8_t pin;
    uint8_t addr;
} imu_config_t;

typedef struct {
    int16_t accel_x;
    int16_t accel_y;
    int16_t accel_z;
    int16_t gyro_x;
    int16_t gyro_y;
    int16_t gyro_z;
    imu_status_t status;
    uint32_t timestamp_ms;
} imu_data_t;

typedef struct {
    identity_t identity;
    imu_config_t config;
    imu_data_t data;
} imu_t;

void init_imu(imu_t* device);
void get_imu(void* ctx);
void set_imu_config(imu_t* device, imu_config_t* config);
void set_imu_identity(imu_t* device, identity_t* identity);

#endif
