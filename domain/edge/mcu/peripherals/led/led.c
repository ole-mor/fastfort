#include "./led.h"
#include <string.h>

void init_led(led_t* device) {
    if (!device) return;
}

void set_led(void* ctx) {
    if (!ctx) return;
    led_t* device = (led_t*)ctx;

    device->data.state = !device->data.state;
    device->data.status = LED_STATUS_OK;
}

void set_led_config(led_t* device, led_config_t* config) {
    if (device && config) {
        device->config = *config;
    }
}

void set_led_identity(led_t* device, identity_t* identity) {
    if (device && identity) {
        device->identity = *identity;
    }
}
