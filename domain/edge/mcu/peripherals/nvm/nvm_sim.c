#include "nvm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FLASH_FILE "sim_flash.bin"
#define FLASH_SIZE 4096

void nvm_init(void) {
    FILE *f = fopen(FLASH_FILE, "rb");
    if (!f) {
        f = fopen(FLASH_FILE, "wb");
        uint8_t *empty = calloc(1, FLASH_SIZE);
        fwrite(empty, 1, FLASH_SIZE, f);
        free(empty);
    }
    fclose(f);
}

void nvm_read(uint32_t offset, void *buf, size_t len) {
    FILE *f = fopen(FLASH_FILE, "rb");
    fseek(f, offset, SEEK_SET);
    fread(buf, 1, len, f);
    fclose(f);
}

void nvm_write(uint32_t offset, const void *buf, size_t len) {
    FILE *f = fopen(FLASH_FILE, "r+b");
    fseek(f, offset, SEEK_SET);
    fwrite(buf, 1, len, f);
    fclose(f);
}

void nvm_erase(uint32_t offset, size_t len) {
    uint8_t *empty = calloc(1, len);
    nvm_write(offset, empty, len);
    free(empty);
}
