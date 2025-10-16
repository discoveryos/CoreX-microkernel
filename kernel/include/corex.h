#ifndef COREX_H
#define COREX_H
#include <stddef.h>
void kernel_panic(const char* message);
void terminal_writestring(const char* str);
void terminal_clear();
#endif
