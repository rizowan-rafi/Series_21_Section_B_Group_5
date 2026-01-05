#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"

#define HEAP_SIZE 65536 

void memory_init(void);
void* kmalloc(uint32_t size);
void kfree(void* ptr);

#endif