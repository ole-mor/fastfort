#ifndef PRES_H
#define PRES_H

#include <stdint.h>
#include "../pe.h"

typedef enum {
    PRES_STATUS_OK,
    PRES_STATUS_STALE,
    PRES_STATUS_FAULT,
    PRES_STATUS_UNKNOWN
} pres_status_t;

typedef struct {
    float warning_threshold_hpa;
    uint32_t interval_ms;
    uint8_t pin;
    uint8_t addr;
} pres_config_t;

typedef struct {
    float pressure_hpa;
    float temperature_c;
    pres_status_t status;
    uint32_t timestamp_ms;
} pres_data_t;

typedef struct {
    identity_t identity;
    pres_config_t config;
    pres_data_t data;
} pres_t;

void init_pres(pres_t* device);
void get_pres(void* ctx);
void set_pres_config(pres_t* device, pres_config_t* config);
void set_pres_identity(pres_t* device, identity_t* identity);

#endif
