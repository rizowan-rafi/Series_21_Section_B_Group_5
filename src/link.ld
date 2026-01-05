/* link.ld - Linker script */
OUTPUT_FORMAT(elf32-i386)
ENTRY(start)

SECTIONS {
    /* The kernel will be loaded at 1MB */
    . = 1M;
    
    .text : {
        /* CRITICAL: Keep the multiboot header at the very beginning */
        KEEP(*(.multiboot))
        *(.text*)
        *(.rodata*)
    }
    
    .data : {
        *(.data*)
    }
    
    .bss : {
        __bss_start = .;
        *(COMMON)
        *(.bss*)
        __bss_end = .;
    }
    
    /* Useful for memory manager to know where free RAM starts */
    . = ALIGN(4096);
    __kernel_end = .;
}