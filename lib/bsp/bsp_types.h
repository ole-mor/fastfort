#ifndef BSP_TYPES_H
#define BSP_TYPES_H 

typedef struct {
    int start;
    int end; 
    int line;
} strloc_t;

typedef struct {
    int count;
    strloc_t** locations;
} find_result_t;

#endif
