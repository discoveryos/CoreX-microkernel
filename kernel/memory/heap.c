#include <stddef.h>
#include <stdint.h>

extern uint32_t placement_address;

void* kmalloc(size_t size) {
    uint32_t temp = placement_address;
    placement_address += size;
    return (void*)temp;
}
