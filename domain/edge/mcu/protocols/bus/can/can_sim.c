#include "can.h"
#include <stdio.h>
#include <string.h>

#define CAN_SIM_MAX_BUSES    2
#define CAN_SIM_QUEUE_SIZE   16
#define CAN_SIM_MAX_DLC      8

typedef struct {
    uint32_t id;
    uint8_t  data[CAN_SIM_MAX_DLC];
    uint8_t  len;
} can_sim_frame_t;

static uint8_t         sim_initialized[CAN_SIM_MAX_BUSES] = {0};
static uint32_t        sim_filter_id[CAN_SIM_MAX_BUSES]   = {0};
static uint32_t        sim_filter_mask[CAN_SIM_MAX_BUSES] = {0};
static uint8_t         sim_filter_active[CAN_SIM_MAX_BUSES] = {0};

// rx queue
static can_sim_frame_t sim_rx_queue[CAN_SIM_MAX_BUSES][CAN_SIM_QUEUE_SIZE];
static uint8_t         sim_rx_head[CAN_SIM_MAX_BUSES] = {0};
static uint8_t         sim_rx_tail[CAN_SIM_MAX_BUSES] = {0};
static uint8_t         sim_rx_count[CAN_SIM_MAX_BUSES] = {0};

static int8_t check_bus(const char* fn, uint8_t bus_id) {
    if (bus_id >= CAN_SIM_MAX_BUSES) {
        printf("[CAN SIM] %s: invalid bus_id %u\n", fn, bus_id);
        return -1;
    }
    return 0;
}

static int passes_filter(uint8_t bus_id, uint32_t id) {
    if (!sim_filter_active[bus_id]) return 1;
    return (id & sim_filter_mask[bus_id]) == (sim_filter_id[bus_id] & sim_filter_mask[bus_id]);
}

// --- public sim helper: inject a CAN frame into the rx queue ---
void can_sim_inject(uint8_t bus_id, uint32_t id, const uint8_t* data, uint8_t len) {
    if (bus_id >= CAN_SIM_MAX_BUSES) return;
    if (sim_rx_count[bus_id] >= CAN_SIM_QUEUE_SIZE) {
        printf("[CAN SIM] bus %u rx queue full, dropping frame id=0x%03X\n", bus_id, id);
        return;
    }
    if (!passes_filter(bus_id, id)) {
        printf("[CAN SIM] bus %u frame id=0x%03X filtered out\n", bus_id, id);
        return;
    }
    can_sim_frame_t* frame = &sim_rx_queue[bus_id][sim_rx_tail[bus_id]];
    frame->id  = id;
    frame->len = len < CAN_SIM_MAX_DLC ? len : CAN_SIM_MAX_DLC;
    memcpy(frame->data, data, frame->len);
    sim_rx_tail[bus_id]  = (sim_rx_tail[bus_id] + 1) % CAN_SIM_QUEUE_SIZE;
    sim_rx_count[bus_id]++;
    printf("[CAN SIM] bus %u injected   id=0x%03X  len=%u  bytes=", bus_id, id, frame->len);
    for (uint8_t i = 0; i < frame->len; i++) printf("%02X ", frame->data[i]);
    printf("\n");
}

// --- hal implementation ---

int8_t can_init(uint8_t bus_id, uint32_t baudrate) {
    if (check_bus("can_init", bus_id) != 0) return -1;
    sim_initialized[bus_id]  = 1;
    sim_filter_active[bus_id] = 0;
    sim_rx_head[bus_id]      = 0;
    sim_rx_tail[bus_id]      = 0;
    sim_rx_count[bus_id]     = 0;
    printf("[CAN SIM] bus %u init  baudrate=%u\n", bus_id, baudrate);
    return 0;
}

int8_t can_deinit(uint8_t bus_id) {
    if (check_bus("can_deinit", bus_id) != 0) return -1;
    sim_initialized[bus_id] = 0;
    printf("[CAN SIM] bus %u deinit\n", bus_id);
    return 0;
}

int8_t can_write(uint8_t bus_id, uint32_t id, const uint8_t* data, uint8_t len) {
    if (check_bus("can_write", bus_id) != 0) return -1;
    if (!sim_initialized[bus_id]) {
        printf("[CAN SIM] bus %u write: not initialized\n", bus_id);
        return -1;
    }
    uint8_t actual_len = len < CAN_SIM_MAX_DLC ? len : CAN_SIM_MAX_DLC;
    printf("[CAN SIM] bus %u write  id=0x%03X  len=%u  bytes=", bus_id, id, actual_len);
    for (uint8_t i = 0; i < actual_len; i++) printf("%02X ", data[i]);
    printf("\n");
    return 0;
}

int8_t can_read(uint8_t bus_id, uint32_t* id, uint8_t* data, uint8_t* len) {
    if (check_bus("can_read", bus_id) != 0) return -1;
    if (sim_rx_count[bus_id] == 0) {
        printf("[CAN SIM] bus %u read: no frames available\n", bus_id);
        return -1;
    }
    can_sim_frame_t* frame = &sim_rx_queue[bus_id][sim_rx_head[bus_id]];
    *id  = frame->id;
    *len = frame->len;
    memcpy(data, frame->data, frame->len);
    sim_rx_head[bus_id]  = (sim_rx_head[bus_id] + 1) % CAN_SIM_QUEUE_SIZE;
    sim_rx_count[bus_id]--;
    printf("[CAN SIM] bus %u read   id=0x%03X  len=%u  bytes=", bus_id, *id, *len);
    for (uint8_t i = 0; i < *len; i++) printf("%02X ", data[i]);
    printf("\n");
    return 0;
}

int8_t can_set_filter(uint8_t bus_id, uint32_t id, uint32_t mask) {
    if (check_bus("can_set_filter", bus_id) != 0) return -1;
    sim_filter_id[bus_id]     = id;
    sim_filter_mask[bus_id]   = mask;
    sim_filter_active[bus_id] = 1;
    printf("[CAN SIM] bus %u filter  id=0x%03X  mask=0x%03X\n", bus_id, id, mask);
    return 0;
}

int16_t can_available(uint8_t bus_id) {
    if (check_bus("can_available", bus_id) != 0) return -1;
    printf("[CAN SIM] bus %u available  frames=%u\n", bus_id, sim_rx_count[bus_id]);
    return sim_rx_count[bus_id];
}

int8_t can_flush(uint8_t bus_id) {
    if (check_bus("can_flush", bus_id) != 0) return -1;
    printf("[CAN SIM] bus %u flush\n", bus_id);
    return 0;
}
