#include "./relay.h"
#include <string.h>

void init_relay(relay_t* device) {
    if (!device) return;
}

void set_relay(void* ctx) {
    if (!ctx) return;
    relay_t* device = (relay_t*)ctx;
    
    device->data.status = RELAY_STATUS_OK;
}

void set_relay_config(relay_t* device, relay_config_t* config) {
    if (device && config) {
        device->config = *config;
    }
}

void set_relay_identity(relay_t* device, identity_t* identity) {
    if (device && identity) {
        device->identity = *identity;
    }
}
