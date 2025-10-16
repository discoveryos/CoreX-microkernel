#include <stdint.h>

inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

inline void outb(uint16_t port, uint8_t data) {
    asm volatile("outb %1, %0" : : "dN" (port), "a" (data));
}

