#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include "../pe.h"

typedef enum {
    INPUT_STATUS_OK,
    INPUT_STATUS_FAULT,
    INPUT_STATUS_UNKNOWN
} input_status_t;

typedef struct {
    uint32_t debounce_ms;
    uint8_t active_low;
    uint32_t interval_ms;
    uint8_t pin;
    uint8_t addr;
} input_config_t;

typedef struct {
    uint8_t state;
    input_status_t status;
    uint32_t timestamp_ms;
} input_data_t;

typedef struct {
    identity_t identity;
    input_config_t config;
    input_data_t data;
} input_t;

void init_input(input_t* device);
void get_input(void* ctx);
void set_input_config(input_t* device, input_config_t* config);
void set_input_identity(input_t* device, identity_t* identity);

#endif
