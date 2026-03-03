#include "./photo.h"
#include <string.h>

void init_photo(photo_t* device) {
    if (!device) return;
}

void get_photo(void* ctx) {
    if (!ctx) return;
    photo_t* device = (photo_t*)ctx;

    if (device->config.addr != 0) {
    } else {
    }

    device->data.status = PHOTO_STATUS_OK;
}

void set_photo_config(photo_t* device, photo_config_t* config) {
    if (device && config) {
        device->config = *config;
    }
}

void set_photo_identity(photo_t* device, identity_t* identity) {
    if (device && identity) {
        device->identity = *identity;
    }
}
