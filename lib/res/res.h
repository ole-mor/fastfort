#ifndef RESULT_H
#define RESULT_H

#include <stdint.h>

#include "../err/err.h"

typedef struct {
    error_code_t code;
    const char *message;
    const char *file;
    int line;
} result_t;

#define RES_SUCCESS \
  (result_t) { .code = OK }

#define RES_IS_OK(r) ((r).code == OK)
#define RES_IS_ERR(r) ((r).code != OK)

#endif
