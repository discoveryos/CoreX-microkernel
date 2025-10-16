#include <stdint.h>
#include <stdbool.h>
#include "idt.h"

idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

extern void isr_handler(void);
extern void keyboard_handler_int(void);

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt_entries[num].base_low = (base & 0xFFFF);
    idt_entries[num].sel = sel;
    idt_entries[num].always0 = 0;
    idt_entries[num].flags = flags;
    idt_entries[num].base_high = (base >> 16) & 0xFFFF;
}

void idt_init() {
    idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
    idt_ptr.base = (uint32_t)&idt_entries;

    // Set up the keyboard handler in the IDT
    idt_set_gate(0x21, (uint32_t)keyboard_handler_int, 0x08, 0x8E);

    asm volatile("lidt (%0)" : : "r" (&idt_ptr));
    asm volatile("sti");
}

