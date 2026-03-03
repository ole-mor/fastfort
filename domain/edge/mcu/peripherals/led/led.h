#ifndef LED_H
#define LED_H

#include <stdint.h>
#include "../pe.h"

typedef enum {
    LED_STATUS_OK,
    LED_STATUS_FAULT,
    LED_STATUS_UNKNOWN
} led_status_t;

typedef struct {
    uint32_t blink_interval_ms;
    uint8_t default_brightness;
    uint8_t pin;
    uint8_t addr;
} led_config_t;

typedef struct {
    uint8_t state; 
    uint8_t brightness;
    led_status_t status;
    uint32_t timestamp_ms;
} led_data_t;

typedef struct {
    identity_t identity;
    led_config_t config;
    led_data_t data;
} led_t;

void init_led(led_t* device);
void set_led(void* ctx);
void set_led_config(led_t* device, led_config_t* config);
void set_led_identity(led_t* device, identity_t* identity);

#endif
