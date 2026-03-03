#ifndef OV2640_H
#define OV2640_H

#include "../cam.h"

#define OV2640_I2C_ADDR 0x30
#define OV2640_PIX_FMT  0x04 // RGB565

static inline cam_t ov2640_default(void) {
    cam_t c = {
        .identity = {
            .id           = "2283a65b-db2a-4df4-a21c-abc123456793",
            .label        = "cam_002",
            .manufacturer = "OmniVision",
            .model        = "OV2640",
            .hw_revision  = "2.0",
            .location     = "",
            .installed    = "2026-03-02",
        },
        .config = {
            .width  = 1600,
            .height = 1200,
            .fps    = 15,
            .format = OV2640_PIX_FMT,
        },
        .data = {
            .frame_ptr    = 0,
            .frame_size   = 0,
            .status       = CAM_STATUS_UNKNOWN,
            .timestamp_ms = 0,
        }
    };
    return c;
}

#endif // OV2640_H
