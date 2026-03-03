#include "mm.h"
#include <stdio.h>

result_t process_valid(void *data, const char *type_name) {
    (void)data;
    printf("  [valid] %s\n", type_name);
    return RES_SUCCESS;
}

result_t process_rejected(void *data, const char *expected_type) {
    (void)data;
    return (result_t){
        .code = ERR_INVALID_TYPE,
        .message = expected_type,
        .file = __FILE__,
        .line = __LINE__,
    };
}
