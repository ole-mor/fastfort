#include "./imu.h"
#include <string.h>

void init_imu(imu_t* device) {
    if (!device) return;
}

void get_imu(void* ctx) {
    if (!ctx) return;
    imu_t* device = (imu_t*)ctx;

    if (device->config.addr != 0) {
    } else {
    }

    device->data.status = IMU_STATUS_OK;
}

void set_imu_config(imu_t* device, imu_config_t* config) {
    if (device && config) {
        device->config = *config;
    }
}

void set_imu_identity(imu_t* device, identity_t* identity) {
    if (device && identity) {
        device->identity = *identity;
    }
}
