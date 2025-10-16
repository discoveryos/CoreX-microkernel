#ifndef VFS_H
#define VFS_H

#include <stddef.h>
#include <stdint.h>

#define MAX_PATH_LEN 128
#define MAX_FD       64

typedef struct {
    int fd;
    char path[MAX_PATH_LEN];
    int flags;
    size_t size;
    uint8_t *data;
} vfs_file_t;

// Mount root filesystem
void mount_rootfs();

// File operations
ipc_message_t fs_open(const char *path, int flags);
ipc_message_t fs_read(int fd, size_t size);
ipc_message_t fs_write(int fd, const void *data, size_t size);

// Internal helpers
vfs_file_t *vfs_lookup_fd(int fd);
vfs_file_t *vfs_lookup_path(const char *path);
int vfs_register(const char *path, uint8_t *data, size_t size, int flags);

#endif
