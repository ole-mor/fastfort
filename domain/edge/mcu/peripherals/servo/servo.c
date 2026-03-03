#include "./servo.h"
#include <string.h>

void init_servo(servo_t* device) {
    if (!device) return;
}

void set_servo_angle(void* ctx) {
    if (!ctx) return;
    servo_t* device = (servo_t*)ctx;
    
    device->data.status = SERVO_STATUS_OK;
}

void set_servo_config(servo_t* device, servo_config_t* config) {
    if (device && config) {
        device->config = *config;
    }
}

void set_servo_identity(servo_t* device, identity_t* identity) {
    if (device && identity) {
        device->identity = *identity;
    }
}
