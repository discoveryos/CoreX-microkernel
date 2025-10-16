#ifndef _IPC_MESSAGE_H
#define _IPC_MESSAGE_H

#include <stdint.h>
#include <stddef.h>

// Message structure
typedef struct {
    uint32_t sender_pid;     ///< The process ID of the sender.
    uint32_t receiver_pid;   ///< The process ID of the receiver.
    uint32_t type;           ///< The type of message (e.g., IPC_GRAPHICS_CMD).
    size_t size;             ///< The size of the message payload.
    char payload[256];       ///< The message payload (example fixed size).
} ipc_message_t;

// IPC message queue structure
typedef struct {
    ipc_message_t *buffer;   ///< A buffer to hold the messages.
    size_t capacity;         ///< The maximum number of messages.
    size_t head;             ///< The index of the next message to read.
    size_t tail;             ///< The index of the next place to write.
    size_t count;            ///< The current number of messages.
} ipc_queue_t;

/**
 * @brief Initializes the IPC message queue for a process.
 * 
 * @param pid The process ID.
 * @return 0 on success, or a negative value on failure.
 */
int ipc_init_queue(uint32_t pid);

/**
 * @brief Sends a message to a destination process.
 * 
 * @param message The message to send.
 * @return 0 on success, or a negative value on failure.
 */
int ipc_send(const ipc_message_t *message);

/**
 * @brief Receives a message for the current process.
 *
 * This function may block if there are no messages to receive.
 *
 * @param message A pointer to a message structure to fill.
 * @return 0 on success, or a negative value on failure.
 */
int ipc_receive(ipc_message_t *message);

#endif // _IPC_MESSAGE_H
