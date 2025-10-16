#include <stdint.h>
#include "include/corex.h"
#include "drivers/vga.c"
#include "log/printk.c"
#include "ipc/ipc.c"

extern void draw_circle(int xc, int yc, int radius, uint32_t color);

void kernel_main() {
    terminal_writestring("CoreX Microkernel Booting...\n");
    _printk("Kernel log: IPC initialized.\n");

    // Clear screen
    terminal_clear();
    
    // Draw initial eyes (will be overwritten by xeyes client)
    draw_circle(200, 200, 50, 0x00FFFFFF);
    draw_circle(350, 200, 50, 0x00FFFFFF);
    
    _printk("Kernel log: Starting xeyes demo.\n");

    // In a real system, the kernel would start the userspace processes.
    // For this demonstration, the demo runs directly in the kernel space.
    // Replace with a real IPC-driven system later.
    
    int mouse_x = 150;
    int mouse_y = 150;
    
    for (int i = 0; i < 100; i++) {
        mouse_x += (i % 2) * 5;
        mouse_y += ((i + 1) % 2) * 5;

        draw_circle(200, 200, 50, 0x00FFFFFF);
        draw_circle(350, 200, 50, 0x00FFFFFF);
        
        // draw_pupil would use the same logic as in xeyes.c
        // For simplicity, we just draw two pupils in a fixed location.
        draw_circle(mouse_x, mouse_y, 15, 0x00000000);
        draw_circle(mouse_x + 150, mouse_y, 15, 0x00000000);
    }
    
    kernel_panic("Kernel has finished demo, halting.");

    while (1) {}
}
// ... (existing code) ...
#include "memory/paging.c"
#include "memory/heap.c"
#include "arch/x86/gdt.c"

// Global variable for the physical memory allocator.
uint32_t placement_address = 0; // Initialize with the start of available physical memory.

void kernel_main() {
    terminal_writestring("CoreX Microkernel Booting...\n");

    // Initialize the GDT and other architecture-specific features.
    gdt_init();
    
    // Initialize the physical memory allocator (placement_address).
    // In a real system, you would get this from the Multiboot structure.
    placement_address = 0x100000; // 1MB, after the kernel image.

    paging_init();

    // The rest of your kernel code can now use virtual memory.
    _printk("Kernel log: Memory management initialized.\n");


    // ... (rest of kernel_main) ...
}
#include "arch/x86/gdt.c"

// Global variable for the physical memory allocator.
uint32_t placement_address = 0; // Initialize with the start of available physical memory.

void kernel_main() {
    terminal_writestring("CoreX Microkernel Booting...\n");

    // Initialize the GDT and other architecture-specific features.
    gdt_init();

    // Initialize the physical memory allocator (placement_address).
    // In a real system, you would get this from the Multiboot structure.
    placement_address = 0x100000; // 1MB, after the kernel image.

    paging_init();

    // The rest of your kernel code can now use virtual memory.
    _printk("Kernel log: Memory management initialized.\n");


    // ... (rest of kernel_main) ...
}
