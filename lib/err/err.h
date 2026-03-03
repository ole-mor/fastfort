#ifndef ERR_H
#define ERR_H

typedef enum {
    OK                      = 0,

    // Type errors 10-19
    ERR_INVALID_TYPE        = 10,
    ERR_TYPE_MISMATCH       = 11,
    ERR_TYPE_OVERFLOW       = 12,
    ERR_TYPE_UNDERFLOW      = 13,
    ERR_TYPE_UNSUPPORTED    = 14,

    // Parse errors 20-29
    ERR_PARSE_FAILED        = 20,
    ERR_INVALID_FORMAT      = 21,
    ERR_UNEXPECTED_TOKEN    = 22,
    ERR_UNEXPECTED_EOF      = 23,
    ERR_ENCODING            = 24,
    ERR_INVALID_ESCAPE      = 25,

    // Lookup errors 30-39
    ERR_NOT_FOUND           = 30,
    ERR_DUPLICATE           = 31,
    ERR_KEY_MISSING         = 32,
    ERR_INDEX_MISSING       = 33,
    ERR_EMPTY               = 34,

    // Memory errors 40-49
    ERR_ALLOC               = 40,
    ERR_NULL                = 41,
    ERR_OUT_OF_BOUNDS       = 42,
    ERR_USE_AFTER_FREE      = 43,
    ERR_DOUBLE_FREE         = 44,
    ERR_BUFFER_OVERFLOW     = 45,
    ERR_ALIGNMENT           = 46,

    // IO errors 50-59
    ERR_FILE_NOT_FOUND      = 50,
    ERR_FILE_READ           = 51,
    ERR_FILE_WRITE          = 52,
    ERR_FILE_PERMISSION     = 53,
    ERR_FILE_EXISTS         = 54,
    ERR_FILE_CLOSED         = 55,
    ERR_FILE_EOF            = 56,
    ERR_PIPE                = 57,

    // Network errors 60-69
    ERR_CONNECTION          = 60,
    ERR_TIMEOUT             = 61,
    ERR_DNS                 = 62,
    ERR_CONNECTION_REFUSED  = 63,
    ERR_CONNECTION_RESET    = 64,
    ERR_SSL                 = 65,
    ERR_INVALID_URL         = 66,
    ERR_HTTP                = 67,

    // System errors 70-79
    ERR_SYSCALL             = 70,
    ERR_PERMISSION          = 71,
    ERR_SIGNAL              = 72,
    ERR_PROCESS             = 73,
    ERR_THREAD              = 74,
    ERR_DEADLOCK            = 75,
    ERR_INTERRUPTED         = 76,

    // Validation errors 80-89
    ERR_REQUIRED            = 80,
    ERR_TOO_SHORT           = 81,
    ERR_TOO_LONG            = 82,
    ERR_TOO_SMALL           = 83,
    ERR_TOO_LARGE           = 84,
    ERR_INVALID_RANGE       = 85,
    ERR_INVALID_VALUE       = 86,
    ERR_INVALID_STATE       = 87,

    // Runtime errors 90-99
    ERR_NOT_IMPLEMENTED     = 90,
    ERR_NOT_SUPPORTED       = 91,
    ERR_DEPRECATED          = 92,
    ERR_INTERNAL            = 93,
    ERR_UNKNOWN             = 99,
} error_code_t;

void handle_err(void);


#endif
