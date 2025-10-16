#include <stdint.h>
#include "../ipc/ipc.h"
#include "../include/syscalls.h"
#include "../arch/x86/io.c"

#define KBD_DATA_PORT 0x60
#define PIC1_COMMAND_PORT 0x20

void keyboard_handler_main() {
    uint8_t scancode = inb(KBD_DATA_PORT);
    outb(PIC1_COMMAND_PORT, 0x20); // Acknowledge the interrupt

    message_t msg;
    msg.type = MSG_KEYBOARD_INPUT;
    msg.data = scancode;
    ipc_send(&msg, TTY_SERVER_ID);
}
