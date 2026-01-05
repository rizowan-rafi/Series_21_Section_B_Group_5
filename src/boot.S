/* Constants for the Multiboot Header */
.set ALIGN,    1<<0             /* align loaded modules on page boundaries */
.set MEMINFO,  1<<1             /* provide memory map */
.set FLAGS,    ALIGN | MEMINFO  /* this is the Multiboot 'flag' field */
.set MAGIC,    0x1BADB002       /* 'magic number' lets bootloader find the header */
.set CHECKSUM, -(MAGIC + FLAGS) /* checksum of above, to prove we are multiboot */

/* * The Multiboot Header 
 * This must be very early in the binary (the linker script handles this)
 */
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/* * The Stack 
 * We reserve 16KB of space in the BSS section for the stack.
 */
.section .bss
.align 16
stack_bottom:
.skip 16384 /* 16 KiB */
stack_top:

/* * The Entry Point 
 * The linker script ENTRY(start) jumps here.
 */
.section .text
.global start
.extern kmain  /* Define the C entry point */

start:
    /* * 1. Set up the Stack Pointer (ESP)
     * C functions need a stack to work. We point ESP to the top of our space.
     */
    mov $stack_top, %esp

    /* * 2. Call the C Kernel
     * We call kmain(). Since kacchiOS's main function is usually named 
     * kmain in typical tutorials, ensure your kernel.c has 'void kmain()'.
     * If your kernel.c uses 'main', change this to 'call main'.
     */
    call kmain

    /* * 3. Infinite Loop
     * If kmain returns, we have nothing to do. Just hang the CPU.
     */
    cli
hang:
    hlt
    jmp hang