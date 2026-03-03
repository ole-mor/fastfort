#include "./cam.h"
#include <string.h>

void init_cam(cam_t* device) {
    if (!device) return;
}

void get_cam(void* ctx) {
    if (!ctx) return;
    cam_t* device = (cam_t*)ctx;

    if (device->config.addr != 0) {
    } else {
    }
    
    device->data.status = CAM_STATUS_OK;
}

void set_cam_config(cam_t* device, cam_config_t* config) {
    if (device && config) {
        device->config = *config;
    }
}

void set_cam_identity(cam_t* device, identity_t* identity) {
    if (device && identity) {
        device->identity = *identity;
    }
}
