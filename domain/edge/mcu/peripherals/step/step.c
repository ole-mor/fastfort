#include "./step.h"
#include <string.h>

void init_step(step_t* device) {
    if (!device) return;
}

void set_step_target(void* ctx) {
    if (!ctx) return;
    step_t* device = (step_t*)ctx;
    
    device->data.status = STEP_STATUS_OK;
}

void set_step_config(step_t* device, step_config_t* config) {
    if (device && config) {
        device->config = *config;
    }
}

void set_step_identity(step_t* device, identity_t* identity) {
    if (device && identity) {
        device->identity = *identity;
    }
}
