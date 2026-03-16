#include "./uart.h"
#include <stdio.h>
#include <Arduino.h>

static HardwareSerial* buses[] = {&Serial, &Serial2, &Serial3};

int8_t uart_init(uint8_t bus_id, uint32_t baudrate) {
    buses[bus_id]->begin(baudrate);
    return 0;
}

int8_t uart_deinit(uint8_t bus_id){
    buses[bus_id]->end();
    return 0;
}

int8_t uart_write(uint8_t bus_id, const uint8_t* data, uint16_t len) {
    buses[bus_id]->write(data, len);
    return 0;
}

int16_t uart_read(uint8_t bus_id, uint8_t* buffer, uint16_t max_len) {
    buses[bus_id]->readBytes(buffer, max_len);
    return 0;
}

int16_t uart_available(uint8_t bus_id){
    buses[bus_id]->available();
    return 0;
}

int8_t uart_flush(uint8_t bus_id){
    buses[bus_id]->flush();
    return 0;
}


