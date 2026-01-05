#include "process.h"
#include "memory.h"
#include "serial.h"

process_t process_table[MAX_PROCESSES];

process_t *current_process = 0;

static uint32_t next_pid = 1;

void process_init() {
    for(int i = 0; i < MAX_PROCESSES; i++) {
        process_table[i].pid = 0;
        process_table[i].state = UNUSED;
        process_table[i].stack_base = 0;
        process_table[i].sp = 0;
        process_table[i].entry = 0;
    }
    
    current_process = 0;
}

int create_process(void (*entry)()) {
    int i;
    for(i = 0; i < MAX_PROCESSES; i++) {
        if(process_table[i].state == UNUSED || process_table[i].state == TERMINATED) {
            break;
        }
    }
    
    if (i == MAX_PROCESSES) return -1;

    serial_puts("[Process Manager] Creating PID ");
    serial_print_dec(next_pid);
    serial_puts("...\n");

    uint32_t* stack_base = (uint32_t*)kmalloc(STACK_SIZE);
    
    if (stack_base == 0) {
        serial_puts("Error: Out of Memory for Stack!\n");
        return -1;
    }

    process_table[i].stack_base = stack_base;

    serial_puts("   -> State: READY\n");
    serial_puts("   -> Stack Allocated: ");
    serial_print_dec(STACK_SIZE);
    serial_puts(" bytes at ");
    serial_print_hex((uint32_t)stack_base);
    serial_puts("\n");

    uint32_t* sp = stack_base + (STACK_SIZE / 4);

    sp--;
    *sp = (uint32_t)entry;

    for(int j = 0; j < 8; j++) {
        sp--;
        *sp = 0; 
    }

    process_table[i].sp = sp;

    process_table[i].pid = next_pid++;
    process_table[i].state = READY;
    process_table[i].entry = entry;

    return process_table[i].pid;
}

void terminate_process(int pid) {
    for(int i = 0; i < MAX_PROCESSES; i++) {
        if(process_table[i].pid == pid) {
            
            serial_puts("[Process Manager] PID ");
            serial_print_dec(pid);
            serial_puts(" Terminated. (State: TERMINATED)\n");
            serial_puts("   -> Freeing Stack Memory...\n");

            process_table[i].state = TERMINATED;
            
            if (process_table[i].stack_base != 0) {
                kfree(process_table[i].stack_base);
                process_table[i].stack_base = 0;
            }
            
            process_table[i].sp = 0;
            break; 
        }
    }
}

process_t* get_current_process() {
    return current_process; 
}