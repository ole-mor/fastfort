#ifndef STEP_H
#define STEP_H

#include <stdint.h>
#include "../pe.h"

typedef enum {
    STEP_STATUS_OK,
    STEP_STATUS_STALL,
    STEP_STATUS_FAULT,
    STEP_STATUS_UNKNOWN
} step_status_t;

typedef struct {
    uint16_t steps_per_rev;
    uint16_t max_rpm;
    uint16_t accel_rate;
    uint32_t interval_ms;
    uint8_t pin;
    uint8_t addr;
} step_config_t;

typedef struct {
    int32_t current_pos;
    int32_t target_pos;
    uint8_t is_moving;
    step_status_t status;
    uint32_t timestamp_ms;
} step_data_t;

typedef struct {
    identity_t identity;
    step_config_t config;
    step_data_t data;
} step_t;

void init_step(step_t* device);
void set_step_target(void* ctx);
void set_step_config(step_t* device, step_config_t* config);
void set_step_identity(step_t* device, identity_t* identity);

#endif
