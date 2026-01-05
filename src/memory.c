#include "memory.h"

struct block_header {
    uint32_t size;
    uint8_t is_free;
    struct block_header *next;
};

static uint8_t heap[HEAP_SIZE];

static struct block_header *head = (void*)heap; 

#define ALIGNMENT 4
uint32_t align_up(uint32_t val) {
    return (val + ALIGNMENT - 1) & ~(ALIGNMENT - 1);
}

void memory_init() {
    head = (void*)heap;
    head->size = HEAP_SIZE - sizeof(struct block_header);
    head->is_free = 1;
    head->next = 0;
}

void* kmalloc(uint32_t size) {
    if (size == 0) return 0;

    uint32_t aligned_size = align_up(size);

    struct block_header *current = head;
    
    while (current != 0) {
        if (current->is_free && current->size >= aligned_size) {
            
            if (current->size > aligned_size + sizeof(struct block_header) + 4) {
                
                struct block_header *new_block = (void*)((uint8_t*)current + sizeof(struct block_header) + aligned_size);
                
                new_block->size = current->size - aligned_size - sizeof(struct block_header);
                new_block->is_free = 1;
                new_block->next = current->next;

                current->size = aligned_size;
                current->next = new_block;
            }

            current->is_free = 0;
            
            return (void*)(current + 1);
        }
        current = current->next;
    }

    return 0;
}

void kfree(void* ptr) {
    if (ptr == 0) return;

    struct block_header *header = (struct block_header*)ptr - 1;
    
    header->is_free = 1;

    struct block_header *current = head;
    while (current != 0 && current->next != 0) {
        
        if (current->is_free && current->next->is_free) {
            
            current->size += sizeof(struct block_header) + current->next->size;
            
            current->next = current->next->next;
            
        } else {
            current = current->next;
        }
    }
}