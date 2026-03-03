#ifndef SERVO_H
#define SERVO_H

#include <stdint.h>
#include "../pe.h"

typedef enum {
    SERVO_STATUS_OK,
    SERVO_STATUS_STALL,
    SERVO_STATUS_FAULT,
    SERVO_STATUS_UNKNOWN
} servo_status_t;

typedef struct {
    uint16_t min_pulse_us;
    uint16_t max_pulse_us;
    uint16_t max_angle_deg;
    uint32_t interval_ms;
    uint8_t pin;
    uint8_t addr;
} servo_config_t;

typedef struct {
    uint16_t current_angle_deg;
    uint16_t target_angle_deg;
    servo_status_t status;
    uint32_t timestamp_ms;
} servo_data_t;

typedef struct {
    identity_t identity;
    servo_config_t config;
    servo_data_t data;
} servo_t;

void init_servo(servo_t* device);
void set_servo_angle(void* ctx);
void set_servo_config(servo_t* device, servo_config_t* config);
void set_servo_identity(servo_t* device, identity_t* identity);

#endif
