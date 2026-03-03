#ifndef OV7670_H
#define OV7670_H

#include "../cam.h"

#define OV7670_I2C_ADDR 0x21
#define OV7670_PIX_FMT  0x04 // RGB565

static inline cam_t ov7670_default(void) {
    cam_t c = {
        .identity = {
            .id           = "e183a65b-db2a-4df4-a21c-abc123456780",
            .label        = "cam_001",
            .manufacturer = "OmniVision",
            .model        = "OV7670",
            .hw_revision  = "rev 2.2",
            .location     = "",
            .installed    = "2026-03-02",
        },
        .config = {
            .width  = 640,
            .height = 480,
            .fps    = 30,
            .format = OV7670_PIX_FMT,
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

#endif // OV7670_H
