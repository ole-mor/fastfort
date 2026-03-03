#ifndef CAN_H
#define CAN_H

#include <stdint.h>

typedef struct {
    uint32_t id;
    uint8_t data[8];
    uint8_t len;
} can_msg_t;

int8_t can_init(uint8_t bus_id, uint32_t bitrate);
int8_t can_write(uint8_t bus_id, const can_msg_t* msg);
int8_t can_read(uint8_t bus_id, can_msg_t* msg);

#endif
