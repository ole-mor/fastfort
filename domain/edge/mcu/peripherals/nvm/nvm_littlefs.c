#include "nvm.h"
#include "lfs.h"

static lfs_t lfs;
static lfs_file_t file;
static const struct lfs_config cfg = {
    .read  = lfs_bd_read,
    .prog  = lfs_bd_prog,
    .erase = lfs_bd_erase,
    .sync  = lfs_bd_sync,
    .read_size      = 16,
    .prog_size      = 16,
    .block_size     = 4096,
    .block_count    = 128,
    .cache_size     = 16,
    .lookahead_size = 16,
    .block_cycles   = 500,
};

void nvm_init(void) {
    if (lfs_mount(&lfs, &cfg) != 0)
        lfs_format(&lfs, &cfg);
        lfs_mount(&lfs, &cfg);
}

void nvm_read(uint32_t offset, void *buf, size_t len) {
    lfs_file_open(&lfs, &file, "nvm", LFS_O_RDONLY);
    lfs_file_seek(&lfs, &file, offset, LFS_SEEK_SET);
    lfs_file_read(&lfs, &file, buf, len);
    lfs_file_close(&lfs, &file);
}

void nvm_write(uint32_t offset, const void *buf, size_t len) {
    lfs_file_open(&lfs, &file, "nvm", LFS_O_WRONLY | LFS_O_CREAT);
    lfs_file_seek(&lfs, &file, offset, LFS_SEEK_SET);
    lfs_file_write(&lfs, &file, buf, len);
    lfs_file_close(&lfs, &file);
}

void nvm_erase(uint32_t offset, size_t len) {
    uint8_t *empty = calloc(1, len);
    nvm_write(offset, empty, len);
    free(empty);
}
