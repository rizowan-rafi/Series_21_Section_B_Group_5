#include "types.h"
#include "serial.h"
#include "memory.h"
#include "process.h"
#include "scheduler.h"

void delay(int count) {
    for (volatile int i = 0; i < count; i++);
}

void task_A() {
    while (1) {
        serial_puts(" [Task A] is running...\n"); 
        
        delay(200000000); 
        
        schedule(); 
    }
}

void task_B() {
    while (1) {
        serial_puts(" [Task B] is running...\n");
        
        delay(200000000);
        
        schedule(); 
    }
}

void task_C() {
    for (int i = 3; i > 0; i--) {
        serial_puts(" [Task C] Countdown: ");
        serial_print_dec(i);
        serial_puts("\n");
        
        delay(200000000);
        
        schedule(); 
    }

    serial_puts(" [Task C] Work done. Killing self...\n");
    
    process_t* me = get_current_process();
    
    terminate_process(me->pid);
    
    schedule(); 
    
    while(1);
}

void kmain() {
    serial_init();
    serial_puts("\n--- kacchiOS Booting  ---\n");

    memory_init();
    process_init();
    scheduler_init();

    int pid1 = create_process(task_A);
    int pid2 = create_process(task_B);
    int pid3 = create_process(task_C);

    if (pid1 < 0 || pid2 < 0 || pid3 < 0) {
        serial_puts("Error: Could not create processes!\n");
        while(1);
    }

    serial_puts("Processes created. Starting Scheduler...\n");

    schedule(); 

    while (1);
}