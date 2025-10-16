#ifndef IPC_H
#define IPC_H
#include <stdbool.h>
#define XORG_SERVER_ID 102
typedef struct { int type; int data; } message_t;
bool ipc_register_server(int server_id);
void ipc_send(void* msg, int dest_id);
void ipc_receive(void* msg, int src_id);
#endif
