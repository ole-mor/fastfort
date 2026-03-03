#ifndef TMP_H
#define TMP_H

#include <stdint.h>
#include "../pe.h"

typedef enum {
    TMP_STATUS_OK,
    TMP_STATUS_STALE,
    TMP_STATUS_OUT_OF_RANGE,
    TMP_STATUS_SENSOR_FAULT,
    TMP_STATUS_UNKNOWN
} tmp_status_t;

typedef struct {
    float alert_low;
    float alert_high;
    uint32_t interval_ms;
    uint8_t pin;   
    uint8_t addr;
} tmp_config_t;

typedef struct {
    int16_t raw;
    tmp_status_t status;
    uint32_t timestamp_ms;
} tmp_data_t;

typedef struct {
    identity_t identity;
    tmp_config_t config;
    tmp_data_t data;
} tmp_t;


void init_tmp(tmp_t* device);
void get_tmp(void* ctx); 
void set_tmp_config(tmp_t* device, tmp_config_t* config);
void set_tmp_identity(tmp_t* device, identity_t* identity);

#endif
