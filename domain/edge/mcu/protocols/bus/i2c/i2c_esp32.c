#include "i2c.h"
#include "driver/i2c.h"

#define I2C_TIMEOUT_MS  1000

int8_t i2c_init(uint8_t bus_id, uint32_t baudrate) {
    i2c_config_t config = {
        .mode             = I2C_MODE_MASTER,
        .sda_io_num       = 21,
        .scl_io_num       = 22,
        .sda_pullup_en    = GPIO_PULLUP_ENABLE,
        .scl_pullup_en    = GPIO_PULLUP_ENABLE,
        .master.clk_speed = baudrate,
    };
    i2c_param_config(bus_id, &config);
    i2c_driver_install(bus_id, I2C_MODE_MASTER, 0, 0, 0);
    return 0;
}

int8_t i2c_deinit(uint8_t bus_id) {
    i2c_driver_delete(bus_id);
    return 0;
}

int8_t i2c_write(uint8_t bus_id, uint8_t addr, const uint8_t* data, uint16_t len) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (addr << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write(cmd, data, len, true);
    i2c_master_stop(cmd);
    esp_err_t err = i2c_master_cmd_begin(bus_id, cmd, pdMS_TO_TICKS(I2C_TIMEOUT_MS));
    i2c_cmd_link_delete(cmd);
    return err == ESP_OK ? 0 : -1;
}

int16_t i2c_read(uint8_t bus_id, uint8_t addr, uint8_t* buf, uint16_t len) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (addr << 1) | I2C_MASTER_READ, true);
    i2c_master_read(cmd, buf, len, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    esp_err_t err = i2c_master_cmd_begin(bus_id, cmd, pdMS_TO_TICKS(I2C_TIMEOUT_MS));
    i2c_cmd_link_delete(cmd);
    return err == ESP_OK ? len : -1;
}

int8_t i2c_write_reg(uint8_t bus_id, uint8_t addr, uint8_t reg, uint8_t value) {
    uint8_t buf[2] = {reg, value};
    return i2c_write(bus_id, addr, buf, 2);
}

int8_t i2c_read_reg(uint8_t bus_id, uint8_t addr, uint8_t reg, uint8_t* value) {
    if (i2c_write(bus_id, addr, &reg, 1) != 0) return -1;
    return i2c_read(bus_id, addr, value, 1) == 1 ? 0 : -1;
}

int8_t i2c_flush(uint8_t bus_id) {
    // ESP-IDF I2C handles flushing internally
    return 0;
}
