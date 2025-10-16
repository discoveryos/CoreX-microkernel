#include <stdint.h>
#include "gdt.h"

// Define the GDT and the GDT pointer
gdt_entry_t gdt_entries[5];
gdt_ptr_t gdt_ptr;

// Function to set up a GDT entry
void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;
    
    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;
    
    gdt_entries[num].granularity |= (granularity & 0xF0);
    gdt_entries[num].access      = access;
}

// Function to initialize the GDT
void gdt_init() {
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
    gdt_ptr.base  = (uint32_t)&gdt_entries;
    
    // Null segment (required)
    gdt_set_gate(0, 0, 0, 0, 0);
    
    // Code segment (kernel)
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    
    // Data segment (kernel)
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    
    // Code segment (user mode)
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    
    // Data segment (user mode)
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
    
    // Load the GDT into the CPU
    asm volatile("lgdt (%0)" : : "r" (&gdt_ptr));
    
    // Flush the segment registers
    asm volatile("mov $0x10, %ax");
    asm volatile("mov %ax, %ds");
    asm volatile("mov %ax, %es");
    asm volatile("mov %ax, %fs");
    asm volatile("mov %ax, %gs");
    asm volatile("mov %ax, %ss");
    
    // Far jump to flush the instruction pipeline
    asm volatile("ljmp $0x08, $kernel_entry");
}
