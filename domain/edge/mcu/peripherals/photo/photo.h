#ifndef PHOTO_H
#define PHOTO_H

#include <stdint.h>
#include "../pe.h"

typedef enum {
    PHOTO_STATUS_OK,
    PHOTO_STATUS_STALE,
    PHOTO_STATUS_FAULT,
    PHOTO_STATUS_UNKNOWN
} photo_status_t;

typedef struct {
    uint16_t threshold_high;
    uint16_t threshold_low;
    uint32_t sample_interval_ms;
    uint8_t pin;   
    uint8_t addr;  
} photo_config_t;

typedef struct {
    uint16_t raw_value;
    uint16_t lux_estimate;
    photo_status_t status;
    uint32_t timestamp_ms;
} photo_data_t;

typedef struct {
    identity_t identity;
    photo_config_t config;
    photo_data_t data;
} photo_t;

void init_photo(photo_t* device);
void get_photo(void* ctx);
void set_photo_config(photo_t* device, photo_config_t* config);
void set_photo_identity(photo_t* device, identity_t* identity);

#endif
