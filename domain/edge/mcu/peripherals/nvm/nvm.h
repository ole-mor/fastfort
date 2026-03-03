#ifndef NVM_H
#define NVM_H

#include <stdint.h>
#include <stddef.h>
#include "../pe.h"

typedef enum {
    NVM_STATUS_OK,
    NVM_STATUS_ERROR,
    NVM_STATUS_BUSY,
    NVM_STATUS_UNKNOWN
} nvm_status_t;

typedef struct {
    uint32_t base_address;
    uint32_t capacity_bytes;
    uint32_t page_size;
} nvm_config_t;

typedef struct {
    uint32_t write_count;
    uint32_t free_bytes;
    nvm_status_t status;
    uint32_t timestamp_ms;
} nvm_data_t;

typedef struct {
    identity_t identity;
    nvm_config_t config;
    nvm_data_t data;
} nvm_t;

void set_nvm_config(nvm_config_t* config);
void set_nvm_identity(identity_t* identity);

// Existing API
void nvm_init(void);
void nvm_read(uint32_t offset, void *buf, size_t len);
void nvm_write(uint32_t offset, const void *buf, size_t len);
void nvm_erase(uint32_t offset, size_t lenint);

#endif
