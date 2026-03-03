#ifndef RELAY_H
#define RELAY_H

#include <stdint.h>
#include "../pe.h"

typedef enum {
    RELAY_STATUS_OK,
    RELAY_STATUS_FAULT,
    RELAY_STATUS_UNKNOWN
} relay_status_t;

typedef struct {
    uint8_t default_state;
    uint32_t pulse_width_ms;
    uint32_t interval_ms;
    uint8_t pin;
    uint8_t addr;
} relay_config_t;

typedef struct {
    uint8_t current_state;
    uint32_t toggle_count;
    relay_status_t status;
    uint32_t timestamp_ms;
} relay_data_t;

typedef struct {
    identity_t identity;
    relay_config_t config;
    relay_data_t data;
} relay_t;

void init_relay(relay_t* device);
void set_relay(void* ctx);
void set_relay_config(relay_t* device, relay_config_t* config);
void set_relay_identity(relay_t* device, identity_t* identity);

#endif
