#include "vfs.h"
#include <string.h>

static vfs_file_t file_table[MAX_FD];
static int next_fd = 3; // 0,1,2 reserved for stdin/out/err

void mount_rootfs() {
    vfs_register("/init", (uint8_t *)"echo coreX booted\n", 18, 0);
    vfs_register("/demo_draw", NULL, 0, 0); // Placeholder
    vfs_register("/demo_echo", NULL, 0, 0); // Placeholder
}

ipc_message_t fs_open(const char *path, int flags) {
    vfs_file_t *file = vfs_lookup_path(path);
    ipc_message_t reply = { .type = IPC_FS_OPEN };
    if (!file) {
        reply.payload.fs_open.fd = -1;
    } else {
        file->fd = next_fd++;
        reply.payload.fs_open.fd = file->fd;
    }
    return reply;
}

ipc_message_t fs_read(int fd, size_t size) {
    vfs_file_t *file = vfs_lookup_fd(fd);
    ipc_message_t reply = { .type = IPC_FS_READ };
    if (!file || !file->data) {
        reply.payload.fs_read.size = 0;
    } else {
        size_t read_size = size < file->size ? size : file->size;
        memcpy(reply.payload.fs_read.data, file->data, read_size);
        reply.payload.fs_read.size = read_size;
    }
    return reply;
}

ipc_message_t fs_write(int fd, const void *data, size_t size) {
    vfs_file_t *file = vfs_lookup_fd(fd);
    ipc_message_t reply = { .type = IPC_FS_WRITE };
    if (!file) {
        reply.payload.fs_write.size = 0;
    } else {
        memcpy(file->data, data, size);
        file->size = size;
        reply.payload.fs_write.size = size;
    }
    return reply;
}

vfs_file_t *vfs_lookup_fd(int fd) {
    for (int i = 0; i < MAX_FD; i++) {
        if (file_table[i].fd == fd) return &file_table[i];
    }
    return NULL;
}

vfs_file_t *vfs_lookup_path(const char *path) {
    for (int i = 0; i < MAX_FD; i++) {
        if (strcmp(file_table[i].path, path) == 0) return &file_table[i];
    }
    return NULL;
}

int vfs_register(const char *path, uint8_t *data, size_t size, int flags) {
    for (int i = 0; i < MAX_FD; i++) {
        if (file_table[i].path[0] == '\0') {
            strncpy(file_table[i].path, path, MAX_PATH_LEN);
            file_table[i].data = data;
            file_table[i].size = size;
            file_table[i].flags = flags;
            return 0;
        }
    }
    return -1;
void mount_rootfs() {
    vfs_register("/demo_draw", (uint8_t *)demo_draw_main, 0, 0);
}
