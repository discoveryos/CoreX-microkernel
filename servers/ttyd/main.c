#include "ipc_message.h"
#include "input.h"

int main() {
    init_keyboard();
    while (1) {
        char key = read_key();
        ipc_message_t msg = {
            .type = IPC_TTY_KEYPRESS,
            .sender_pid = TTY_CHANNEL,
            .target_pid = SHELL_PID,
            .payload.tty_keypress.key = key
        };
        ipc_send(msg);
    }
}
