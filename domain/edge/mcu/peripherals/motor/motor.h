#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>
#include "../pe.h"

typedef enum {
    MOTOR_STATUS_OK,
    MOTOR_STATUS_STALL,
    MOTOR_STATUS_FAULT,
    MOTOR_STATUS_UNKNOWN
} motor_status_t;

typedef struct {
    uint32_t max_speed_rpm;
    uint8_t invert_direction;
    uint32_t interval_ms;
    uint8_t pin;
    uint8_t addr;
} motor_config_t;

typedef struct {
    int32_t current_speed_rpm;
    motor_status_t status;
    uint32_t timestamp_ms;
} motor_data_t;

typedef struct {
    identity_t identity;
    motor_config_t config;
    motor_data_t data;
} motor_t;

void init_motor(motor_t* device);
void set_motor_speed(void* ctx);
void set_motor_config(motor_t* device, motor_config_t* config);
void set_motor_identity(motor_t* device, identity_t* identity);

#endif
