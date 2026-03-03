#include "./pr.h"
#include <stddef.h>

#define MAX_TASKS 32

static task_t tasks[MAX_TASKS];
static uint8_t task_count = 0;

__attribute__((weak)) uint32_t sys_time_ms(void) {
    static uint32_t sys_ticks = 0;
    return sys_ticks++;
}

void init_tasks(void) {
    task_count = 0;
}

int8_t register_task(poll_func_t poll, dispatch_func_t dispatch, void* ctx, uint32_t interval_ms, uint32_t debounce_ms) {
    if (task_count >= MAX_TASKS) {
        return -1;
    }
    if (poll == NULL) {
        return -2;
    }

    tasks[task_count].poll_func = poll;
    tasks[task_count].dispatch_func = dispatch;
    tasks[task_count].ctx = ctx;
    tasks[task_count].interval_ms = interval_ms;
    tasks[task_count].min_debounce_ms = debounce_ms;
    tasks[task_count].last_poll_ms = 0;
    tasks[task_count].last_trigger_ms = 0;
    
    task_count++;
    return 0;
}

uint8_t check_debounce(uint32_t* last_trigger, uint32_t debounce_interval) {
    if (debounce_interval == 0) return 1;

    uint32_t current_ms = sys_time_ms();
    if (current_ms - *last_trigger >= debounce_interval) {
        *last_trigger = current_ms;
        return 1;
    }
    return 0;
}

void process_tasks(void) {
    uint32_t current_ms = sys_time_ms();

    for (uint8_t i = 0; i < task_count; i++) {
        task_t* task = &tasks[i];

        if (current_ms - task->last_poll_ms >= task->interval_ms && 
            current_ms - task->last_trigger_ms >= task->min_debounce_ms) {
            
            task->last_poll_ms = current_ms;
            task->last_trigger_ms = current_ms;

            if (task->poll_func) {
                task->poll_func(task->ctx);
            }

            if (task->dispatch_func) {
                task->dispatch_func(task->ctx);
            }
        }
    }
}
