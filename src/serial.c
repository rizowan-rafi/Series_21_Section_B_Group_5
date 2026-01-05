#include "serial.h"

#define PORT 0x3f8

void serial_init() {
}

void serial_putc(char c) {
    __asm__ volatile ("outb %0, %1" : : "a"(c), "Nd"(PORT));
}

void serial_puts(const char* str) {
    while (*str) {
        serial_putc(*str++);
    }
}

void serial_print_dec(uint32_t num) {
    if (num == 0) { serial_putc('0'); return; }
    
    char buffer[12];
    int i = 0;
    while (num > 0) {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }
    while (--i >= 0) serial_putc(buffer[i]);
}

void serial_print_hex(uint32_t num) {
    serial_puts("0x");
    char hex[] = "0123456789ABCDEF";
    for (int i = 28; i >= 0; i -= 4) {
        serial_putc(hex[(num >> i) & 0xF]);
    }
}