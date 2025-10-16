section .multiboot_header
.align 8
multiboot_header:
    .long 0xe85250d6 ; Multiboot 2 magic number
    .long 0 ; protected mode i386
    .long multiboot_header_end - multiboot_header
    .long -(0xe85250d6 + 0 + (multiboot_header_end - multiboot_header))
multiboot_header_end:

section .text
.globl _start
_start:
    cli ; Clear all interrupts
    
    ; Setup a stack
    mov esp, stack_top
    
    ; Call the C kernel_main function
    call kernel_main
    
    ; Halt the CPU if kernel_main returns
    jmp .

section .bss
.align 4
stack_bottom:
    .skip 16384 ; 16 KiB stack
stack_top:
