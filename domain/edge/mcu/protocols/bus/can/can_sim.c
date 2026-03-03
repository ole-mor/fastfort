#include "./can.h"
#include <stdio.h>

int8_t can_init(uint8_t bus_id, uint32_t bitrate) {
    printf("[SIM] CAN Init Bus: %u, Bitrate: %u\n", bus_id, bitrate);
    return 0;
}

int8_t can_write(uint8_t bus_id, const can_msg_t* msg) {
    printf("[SIM] CAN Write Bus: %u, ID: 0x%03X, Len: %u, Data: ", bus_id, msg->id, msg->len);
    for (uint8_t i = 0; i < msg->len; i++) {
        printf("%02X ", msg->data[i]);
    }
    printf("\n");
    return 0;
}

int8_t can_read(uint8_t bus_id, can_msg_t* msg) {
    printf("[SIM] CAN Read Bus: %u\n", bus_id);
    return 0;
}
