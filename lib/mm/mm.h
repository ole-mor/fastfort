#ifndef META_MACROS_H
#define META_MACROS_H

#include "../res/res.h"

// Generic macro to check type at compile time and process
#define process(x, T) _Generic((x),                 \
    T:                      process_valid,          \
    default:                process_rejected        \
)(&(x), #T)

#define allowed_type(x, T) _Generic((x),            \
    T: 1,                                           \
    default: 0                                      \
)

result_t process_valid(void *data, const char *type_name);
result_t process_rejected(void *data, const char *expected_type);

#endif
