#include "shell.h"
#include "commands.h"
#include "syscall.h"
#include "vt.h"
#include <string.h>

#define MAX_CMD_LEN 128
static char cmd_buffer[MAX_CMD_LEN];
static int cmd_index = 0;

void shell_loop() {
    char key;
    sys_write(STDOUT, "> ", 2); // Prompt

    while (1) {
        if (sys_read(STDIN, &key, 1)) {
            if (key == '\n') {
                cmd_buffer[cmd_index] = '\0';
                sys_write(STDOUT, "\n", 1);
                execute_command(cmd_buffer);
                cmd_index = 0;
                sys_write(STDOUT, "> ", 2);
            } else if (key == '\b') {
                if (cmd_index > 0) {
                    cmd_index--;
                    sys_write(STDOUT, "\b \b", 3); // Erase character
                }
            } else if (key == '\t') {
                // Optional: autocomplete
            } else {
                if (cmd_index < MAX_CMD_LEN - 1) {
                    cmd_buffer[cmd_index++] = key;
                    sys_write(STDOUT, &key, 1); // Echo
                }
            }
        }
    }
}

void execute_command(const char *cmd) {
    if (strcmp(cmd, "clear") == 0) {
        cmd_clear();
    } else if (strcmp(cmd, "demo_draw") == 0) {
        cmd_demo_draw();
    } else if (strcmp(cmd, "demo_echo") == 0) {
        cmd_demo_echo();
    } else if (strcmp(cmd, "help") == 0) {
        cmd_help();
    } else {
        const char *msg = "Unknown command\n";
        sys_write(STDOUT, msg, strlen(msg));
    }
void execute_command(const char *cmd) {
    if (strcmp(cmd, "demo_draw") == 0) cmd_demo_draw();
    // other commands...
}
