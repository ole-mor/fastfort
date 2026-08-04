#include "i2c.h"
#include <stdio.h>
#include <string.h>

#define I2C_SIM_MAX_BUSES    2
#define I2C_SIM_MAX_DEVICES  16
#define I2C_SIM_REG_SIZE     256

static uint8_t  sim_initialized[I2C_SIM_MAX_BUSES] = {0};

// per-device register map for simulation
typedef struct {
    uint8_t addr;
    uint8_t regs[I2C_SIM_REG_SIZE];
    uint8_t active;
} i2c_sim_device_t;

static i2c_sim_device_t sim_devices[I2C_SIM_MAX_BUSES][I2C_SIM_MAX_DEVICES];

static int8_t check_bus(const char* fn, uint8_t bus_id) {
    if (bus_id >= I2C_SIM_MAX_BUSES) {
        printf("[I2C SIM] %s: invalid bus_id %u\n", fn, bus_id);
        return -1;
    }
    return 0;
}

static i2c_sim_device_t* find_device(uint8_t bus_id, uint8_t addr) {
    for (int i = 0; i < I2C_SIM_MAX_DEVICES; i++) {
        if (sim_devices[bus_id][i].active && sim_devices[bus_id][i].addr == addr)
            return &sim_devices[bus_id][i];
    }
    return NULL;
}

// --- public sim helper: register a device with preset register values ---
void i2c_sim_add_device(uint8_t bus_id, uint8_t addr, const uint8_t* regs, uint16_t len) {
    if (bus_id >= I2C_SIM_MAX_BUSES) return;
    for (int i = 0; i < I2C_SIM_MAX_DEVICES; i++) {
        if (!sim_devices[bus_id][i].active) {
            sim_devices[bus_id][i].active = 1;
            sim_devices[bus_id][i].addr   = addr;
            if (regs && len > 0) {
                uint16_t copy = len < I2C_SIM_REG_SIZE ? len : I2C_SIM_REG_SIZE;
                memcpy(sim_devices[bus_id][i].regs, regs, copy);
            }
            printf("[I2C SIM] device registered  bus=%u addr=0x%02X\n", bus_id, addr);
            return;
        }
    }
    printf("[I2C SIM] i2c_sim_add_device: no free slots on bus %u\n", bus_id);
}

// --- hal implementation ---

int8_t i2c_init(uint8_t bus_id, uint32_t baudrate) {
    if (check_bus("i2c_init", bus_id) != 0) return -1;
    sim_initialized[bus_id] = 1;
    memset(sim_devices[bus_id], 0, sizeof(sim_devices[bus_id]));
    printf("[I2C SIM] bus %u init  baudrate=%u\n", bus_id, baudrate);
    return 0;
}

int8_t i2c_deinit(uint8_t bus_id) {
    if (check_bus("i2c_deinit", bus_id) != 0) return -1;
    sim_initialized[bus_id] = 0;
    printf("[I2C SIM] bus %u deinit\n", bus_id);
    return 0;
}

int8_t i2c_write(uint8_t bus_id, uint8_t addr, const uint8_t* data, uint16_t len) {
    if (check_bus("i2c_write", bus_id) != 0) return -1;
    i2c_sim_device_t* dev = find_device(bus_id, addr);
    if (!dev) {
        printf("[I2C SIM] bus %u write  addr=0x%02X  no device at address\n", bus_id, addr);
        return -1;
    }
    printf("[I2C SIM] bus %u write  addr=0x%02X  len=%-4u  bytes=", bus_id, addr, len);
    for (uint16_t i = 0; i < len; i++) printf("%02X ", data[i]);
    printf("\n");
    return 0;
}

int16_t i2c_read(uint8_t bus_id, uint8_t addr, uint8_t* buf, uint16_t len) {
    if (check_bus("i2c_read", bus_id) != 0) return -1;
    i2c_sim_device_t* dev = find_device(bus_id, addr);
    if (!dev) {
        printf("[I2C SIM] bus %u read   addr=0x%02X  no device at address\n", bus_id, addr);
        return -1;
    }
    memcpy(buf, dev->regs, len < I2C_SIM_REG_SIZE ? len : I2C_SIM_REG_SIZE);
    printf("[I2C SIM] bus %u read   addr=0x%02X  len=%-4u  bytes=", bus_id, addr, len);
    for (uint16_t i = 0; i < len; i++) printf("%02X ", buf[i]);
    printf("\n");
    return len;
}

int8_t i2c_write_reg(uint8_t bus_id, uint8_t addr, uint8_t reg, uint8_t value) {
    if (check_bus("i2c_write_reg", bus_id) != 0) return -1;
    i2c_sim_device_t* dev = find_device(bus_id, addr);
    if (!dev) {
        printf("[I2C SIM] bus %u write_reg  addr=0x%02X  no device at address\n", bus_id, addr);
        return -1;
    }
    dev->regs[reg] = value;
    printf("[I2C SIM] bus %u write_reg  addr=0x%02X  reg=0x%02X  value=0x%02X\n", bus_id, addr, reg, value);
    return 0;
}

int8_t i2c_read_reg(uint8_t bus_id, uint8_t addr, uint8_t reg, uint8_t* value) {
    if (check_bus("i2c_read_reg", bus_id) != 0) return -1;
    i2c_sim_device_t* dev = find_device(bus_id, addr);
    if (!dev) {
        printf("[I2C SIM] bus %u read_reg   addr=0x%02X  no device at address\n", bus_id, addr);
        return -1;
    }
    *value = dev->regs[reg];
    printf("[I2C SIM] bus %u read_reg   addr=0x%02X  reg=0x%02X  value=0x%02X\n", bus_id, addr, reg, *value);
    return 0;
}

int8_t i2c_flush(uint8_t bus_id) {
    if (check_bus("i2c_flush", bus_id) != 0) return -1;
    printf("[I2C SIM] bus %u flush\n", bus_id);
    return 0;
}
