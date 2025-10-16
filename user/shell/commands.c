#include "commands.h"
#include "syscall.h"

void cmd_clear() {
    fb_clear(0x000000); // Clear screen to black
}

void cmd_demo_draw() {
    exec("/demo_draw"); // Launch pixel demo
}

void cmd_demo_echo() {
    exec("/demo_echo"); // Launch echo app
}

void cmd_help() {
    const char *msg =
        "Available commands:\n"
        "  clear       - Clear the screen\n"
        "  demo_draw   - Draw a red square\n"
        "  demo_echo   - Echo typed keys\n"
        "  help        - Show this help\n";
    sys_write(STDOUT, msg, strlen(msg));
void cmd_demo_draw() {
    int pid = exec("/demo_draw");
    if (pid < 0)
        sys_write(STDOUT, "Failed to launch demo_draw\n", 28);
}
