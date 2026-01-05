#include "scheduler.h"
#include "process.h"
#include "serial.h"

extern process_t process_table[]; 
extern process_t *current_process; 

static int current_process_index = -1;

void scheduler_init() {
    current_process_index = -1;
}

__attribute__((naked)) void ctx_switch(uint32_t **old_sp, uint32_t *new_sp) {
    __asm__ volatile (
        "pusha\n\t"
        "movl 36(%esp), %eax\n\t"
        "movl %esp, (%eax)\n\t"
        "movl 40(%esp), %esp\n\t"
        "popa\n\t"
        "ret\n\t"
    );
}

void schedule() {
    int prev_index = current_process_index;
    int next_index = (current_process_index + 1) % MAX_PROCESSES;
    int found = 0;

    for(int i = 0; i < MAX_PROCESSES; i++) {
        int idx = (next_index + i) % MAX_PROCESSES;
        if(process_table[idx].state == READY) {
            current_process_index = idx;
            found = 1;
            break;
        }
    }

    if (!found) return;
    if (prev_index == current_process_index) return;

    process_t *prev = &process_table[prev_index];
    process_t *next = &process_table[current_process_index];

    serial_puts("\n[Scheduler] Context Switch:\n");
    
    if (prev->state == CURRENT) {
        serial_puts("   PID ");
        serial_print_dec(prev->pid);
        serial_puts(" (CURRENT) -> READY\n");
        prev->state = READY;
    } else if (prev->state == TERMINATED) {
         serial_puts("   PID ");
         serial_print_dec(prev->pid);
         serial_puts(" (TERMINATED) -> Skipping\n");
    }

    serial_puts("   PID ");
    serial_print_dec(next->pid);
    serial_puts(" (READY)   -> CURRENT\n");

    next->state = CURRENT;
    
    current_process = next; 

    ctx_switch(&prev->sp, next->sp);
}