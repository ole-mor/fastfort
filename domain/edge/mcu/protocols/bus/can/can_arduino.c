#include "can.h"
#include <Arduino.h>
#include <CAN.h>   // arduino-CAN library

int8_t can_init(uint8_t bus_id, uint32_t baudrate) {
    if (!CAN.begin(baudrate)) return -1;
    return 0;
}

int8_t can_deinit(uint8_t bus_id) {
    CAN.end();
    return 0;
}

int8_t can_write(uint8_t bus_id, uint32_t id, const uint8_t* data, uint8_t len) {
    CAN.beginPacket(id);
    CAN.write(data, len);
    CAN.endPacket();
    return 0;
}

int8_t can_read(uint8_t bus_id, uint32_t* id, uint8_t* data, uint8_t* len) {
    int packetSize = CAN.parsePacket();
    if (packetSize <= 0) return -1;
    *id  = CAN.packetId();
    *len = 0;
    while (CAN.available() && *len < packetSize) {
        data[(*len)++] = CAN.read();
    }
    return 0;
}

int8_t can_set_filter(uint8_t bus_id, uint32_t id, uint32_t mask) {
    CAN.filter(id, mask);
    return 0;
}

int16_t can_available(uint8_t bus_id) {
    return CAN.parsePacket() > 0 ? 1 : 0;
}

int8_t can_flush(uint8_t bus_id) {
    // CAN packets are sent immediately, no flush needed
    return 0;
}
