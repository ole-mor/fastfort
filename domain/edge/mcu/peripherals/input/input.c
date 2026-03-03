#include "./input.h"
#include <string.h>

void init_input(input_t* device) {
    if (!device) return;
}

void get_input(void* ctx) {
    if (!ctx) return;
    input_t* device = (input_t*)ctx;

    device->data.status = INPUT_STATUS_OK;
}

void set_input_config(input_t* device, input_config_t* config) {
    if (device && config) {
        device->config = *config;
    }
}

void set_input_identity(input_t* device, identity_t* identity) {
    if (device && identity) {
        device->identity = *identity;
    }
}
