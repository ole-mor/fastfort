#include "nvm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STORAGE_PATH "/var/lib/myapp/nvm.bin"
#define STORAGE_SIZE 4096

void nvm_init(void) {
    FILE *f = fopen(STORAGE_PATH, "rb");
    if (!f) {
        f = fopen(STORAGE_PATH, "wb");
        uint8_t *empty = calloc(1, STORAGE_SIZE);
        fwrite(empty, 1, STORAGE_SIZE, f);
        free(empty);
    }
    fclose(f);
}

void nvm_read(uint32_t offset, void *buf, size_t len) {
    FILE *f = fopen(STORAGE_PATH, "rb");
    fseek(f, offset, SEEK_SET);
    fread(buf, 1, len, f);
    fclose(f);
}

void nvm_write(uint32_t offset, const void *buf, size_t len) {
    FILE *f = fopen(STORAGE_PATH, "r+b");
    fseek(f, offset, SEEK_SET);
    fwrite(buf, 1, len, f);
    fclose(f);
}

void nvm_erase(uint32_t offset, size_t len) {
    uint8_t *empty = calloc(1, len);
    nvm_write(offset, empty, len);
    free(empty);
}
