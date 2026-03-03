#include "nvm.h"
#include "nvs_flash.h"
#include "nvs.h"

static nvs_handle_t handle;

void nvm_init(void) {
    nvs_flash_init();
    nvs_open("s", NVS_READWRITE, &handle);
}

void nvm_read(uint32_t offset, void *buf, size_t len) {
    char key[11];
    snprintf(key, sizeof(key), "%lu", (unsigned long)offset);
    nvs_get_blob(handle, key, buf, &len);
}

void nvm_write(uint32_t offset, const void *buf, size_t len) {
    char key[11];
    snprintf(key, sizeof(key), "%lu", (unsigned long)offset);
    nvs_set_blob(handle, key, buf, len);
    nvs_commit(handle);
}

void nvm_erase(uint32_t offset, size_t len) {
    char key[11];
    snprintf(key, sizeof(key), "%lu", (unsigned long)offset);
    nvs_erase_key(handle, key);
    nvs_commit(handle);
}
