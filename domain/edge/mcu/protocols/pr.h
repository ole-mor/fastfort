#ifndef PR_H
#define PR_H

#include <stdint.h>

typedef void (*poll_func_t)(void* ctx);

typedef void (*dispatch_func_t)(void* ctx);

typedef struct {
    poll_func_t poll_func;             
    dispatch_func_t dispatch_func;     
    void* ctx;                         
    uint32_t interval_ms;              
    uint32_t min_debounce_ms;          
    uint32_t last_poll_ms;             
    uint32_t last_trigger_ms;          
} task_t;

void init_tasks(void);
int8_t register_task(poll_func_t poll, dispatch_func_t dispatch, void* ctx, uint32_t interval_ms, uint32_t debounce_ms);
void process_tasks(void);
uint8_t check_debounce(uint32_t* last_trigger, uint32_t debounce_interval);
uint32_t sys_time_ms(void);

#endif
