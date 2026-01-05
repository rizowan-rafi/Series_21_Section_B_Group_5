#ifndef PROCESS_H
#define PROCESS_H
#include "types.h" 

#define MAX_PROCESSES 10
#define STACK_SIZE 2048

typedef enum {
    UNUSED,
    CURRENT,
    READY,
    TERMINATED
} process_state;

typedef struct {
    uint32_t pid;
    process_state state;
    void* stack_base;
    uint32_t* sp;
    void (*entry)();
} process_t;

extern process_t process_table[MAX_PROCESSES]; 

void process_init();
int create_process(void (*entry)());
void terminate_process(int pid);
process_t* get_current_process();

#endif