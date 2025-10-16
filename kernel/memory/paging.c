#include <stdint.h>
#include <stdbool.h>

#define PAGE_PRESENT 0x001
#define PAGE_RW 0x002
#define PAGE_USER 0x004

typedef uint32_t page_directory_t[1024];
typedef uint32_t page_table_t[1024];

page_directory_t *kernel_directory;
extern uint32_t placement_address;

void paging_init() {
    kernel_directory = (page_directory_t*)placement_address;
    placement_address += sizeof(page_directory_t);

    page_table_t *table = (page_table_t*)placement_address;
    placement_address += sizeof(page_table_t);

    for (uint32_t i = 0; i < 1024; i++) {
        (*table)[i] = (i * 0x1000) | PAGE_PRESENT | PAGE_RW;
    }
    (*kernel_directory)[0] = (uint32_t)table | PAGE_PRESENT | PAGE_RW;

    asm volatile("mov %0, %%cr3" :: "r"(kernel_directory));
    uint32_t cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= 0x80000000;
    asm volatile("mov %0, %%cr0" :: "r"(cr0));

    _printk("Paging enabled.\n");
}
