#include "ipc_message.h"
#include "vfs.h"

int main() {
    mount_rootfs();
    while (1) {
        ipc_message_t msg = ipc_recv(FS_CHANNEL);
        ipc_message_t reply;
        if (msg.type == IPC_FS_OPEN)
            reply = fs_open(msg.payload.fs_open.path, msg.payload.fs_open.flags);
        else if (msg.type == IPC_FS_READ)
            reply = fs_read(msg.payload.fs_read.fd, msg.payload.fs_read.size);
        else if (msg.type == IPC_FS_WRITE)
            reply = fs_write(msg.payload.fs_write.fd, msg.payload.fs_write.data, msg.payload.fs_write.size);
        ipc_send(msg.sender_pid, reply);
    }
}
