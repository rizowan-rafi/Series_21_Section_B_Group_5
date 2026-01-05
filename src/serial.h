#ifndef SERIAL_H
#define SERIAL_H
#include "types.h"

void serial_init(void);
void serial_putc(char c);
void serial_puts(const char* str);
void serial_print_dec(uint32_t num); 
void serial_print_hex(uint32_t num); 

#endif