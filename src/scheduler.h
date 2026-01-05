#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "process.h"


void scheduler_init();


void schedule();

void ctx_switch(uint32_t **old_sp, uint32_t *new_sp);

#endif