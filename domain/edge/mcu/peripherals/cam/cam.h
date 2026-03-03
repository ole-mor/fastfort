#ifndef CAM_H
#define CAM_H

#include <stdint.h>
#include "../pe.h"

typedef enum {
    CAM_STATUS_OK,
    CAM_STATUS_STALE,
    CAM_STATUS_BUSY,
    CAM_STATUS_FAULT,
    CAM_STATUS_UNKNOWN
} cam_status_t;

typedef struct {
    uint16_t width;
    uint16_t height;
    uint8_t fps;
    uint8_t format;
    uint32_t interval_ms;
    uint8_t pin;
    uint8_t addr;
} cam_config_t;

typedef struct {
    uint8_t* frame_ptr;
    uint32_t frame_size;
    cam_status_t status;
    uint32_t timestamp_ms;
} cam_data_t;

typedef struct {
    identity_t identity;
    cam_config_t config;
    cam_data_t data;
} cam_t;

void init_cam(cam_t* device);
void get_cam(void* ctx);
void set_cam_config(cam_t* device, cam_config_t* config);
void set_cam_identity(cam_t* device, identity_t* identity);

#endif
