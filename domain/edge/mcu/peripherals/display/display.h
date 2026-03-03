#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include "../pe.h"

typedef enum {
    DISPLAY_STATUS_OK,
    DISPLAY_STATUS_BUSY,
    DISPLAY_STATUS_FAULT,
    DISPLAY_STATUS_UNKNOWN
} display_status_t;

typedef struct {
    uint16_t width;
    uint16_t height;
    uint8_t rotation;
    uint8_t brightness;
    uint32_t interval_ms;
    uint8_t pin;
    uint8_t addr;
} display_config_t;

typedef struct {
    uint32_t update_count;
    display_status_t status;
    uint32_t timestamp_ms;
} display_data_t;

typedef struct {
    identity_t identity;
    display_config_t config;
    display_data_t data;
} display_t;

void init_display(display_t* device);
void update_display(void* ctx);
void set_display_config(display_t* device, display_config_t* config);
void set_display_identity(display_t* device, identity_t* identity);

#endif
