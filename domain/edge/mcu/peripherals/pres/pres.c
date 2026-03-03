#include "./pres.h"
#include <string.h>

void init_pres(pres_t* device) {
    if (!device) return;
}

void get_pres(void* ctx) {
    if (!ctx) return;
    pres_t* device = (pres_t*)ctx;

    if (device->config.addr != 0) {
    } else {
    }
    
    device->data.status = PRES_STATUS_OK;
}

void set_pres_config(pres_t* device, pres_config_t* config) {
    if (device && config) {
        device->config = *config;
    }
}

void set_pres_identity(pres_t* device, identity_t* identity) {
    if (device && identity) {
        device->identity = *identity;
    }
}
