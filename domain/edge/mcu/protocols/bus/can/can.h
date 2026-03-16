#ifndef CAN_H
#define CAN_H

#include <stdint.h>

int8_t  can_init(uint8_t bus_id, uint32_t baudrate);
int8_t  can_deinit(uint8_t bus_id);
int8_t  can_write(uint8_t bus_id, uint32_t id, const uint8_t* data, uint8_t len);
int8_t  can_read(uint8_t bus_id, uint32_t* id, uint8_t* data, uint8_t* len);
int8_t  can_set_filter(uint8_t bus_id, uint32_t id, uint32_t mask);
int16_t can_available(uint8_t bus_id);
int8_t  can_flush(uint8_t bus_id);

#endif
