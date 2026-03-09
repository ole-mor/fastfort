#include "./tmp.h"
#include <string.h>

void init_tmp(tmp_t* device) {
    if (!device) return;
}

void get_tmp(void* ctx) {
    if (!ctx) return;
    tmp_t* device = (tmp_t*)ctx;

    if (device->config.addr != 0) {
    } else {
        // 
    }

    device->data.status = TMP_STATUS_OK;
}

void set_tmp_config(tmp_t* device, tmp_config_t* config) {
    if (device && config) {
        device->config = *config;
    }
}

void set_tmp_identity(tmp_t* device, identity_t* identity) {
    if (device && identity) {
        device->identity = *identity;
    }
}
