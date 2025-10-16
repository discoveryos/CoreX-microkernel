#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include "../include/corex.h"

#define LOG_BUFFER_SIZE 4096
typedef struct { char data[LOG_BUFFER_SIZE]; uint32_t head; uint32_t tail; } log_ring_buffer_t;
log_ring_buffer_t log_buffer;

void _printk(const char* format, ...) {
    // Simplified implementation for demonstration
    terminal_writestring(format);
}

void kernel_panic(const char* message) {
    terminal_clear();
    terminal_writestring("COREX KERNEL PANIC\n");
    terminal_writestring(message);
    while(1){}
}
