#include "can.h"
#include "driver/twai.h"

int8_t can_init(uint8_t bus_id, uint32_t baudrate) {
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(GPIO_NUM_21, GPIO_NUM_22, TWAI_MODE_NORMAL);
    twai_timing_config_t  t_config = TWAI_TIMING_CONFIG_500KBITS();  // default 500k
    twai_filter_config_t  f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();
    twai_driver_install(&g_config, &t_config, &f_config);
    twai_start();
    return 0;
}

int8_t can_deinit(uint8_t bus_id) {
    twai_stop();
    twai_driver_uninstall();
    return 0;
}

int8_t can_write(uint8_t bus_id, uint32_t id, const uint8_t* data, uint8_t len) {
    twai_message_t msg = {
        .identifier      = id,
        .data_length_code = len,
    };
    for (uint8_t i = 0; i < len; i++) msg.data[i] = data[i];
    return twai_transmit(&msg, pdMS_TO_TICKS(100)) == ESP_OK ? 0 : -1;
}

int8_t can_read(uint8_t bus_id, uint32_t* id, uint8_t* data, uint8_t* len) {
    twai_message_t msg;
    if (twai_receive(&msg, pdMS_TO_TICKS(100)) != ESP_OK) return -1;
    *id  = msg.identifier;
    *len = msg.data_length_code;
    for (uint8_t i = 0; i < *len; i++) data[i] = msg.data[i];
    return 0;
}

int8_t can_set_filter(uint8_t bus_id, uint32_t id, uint32_t mask) {
    // ESP32 TWAI filters are set at init time, not dynamically
    // requires reinit to change — left as extension point
    return 0;
}

int16_t can_available(uint8_t bus_id) {
    twai_status_info_t status;
    twai_get_status_info(&status);
    return (int16_t)status.msgs_to_rx;
}

int8_t can_flush(uint8_t bus_id) {
    twai_clear_transmit_queue();
    return 0;
}
