#include "ipc_message.h"
#include "framebuffer.h"

int main() {
    init_framebuffer();
    init_cursor();
    while (1) {
        ipc_message_t msg = ipc_recv(GFX_CHANNEL);
        if (msg.type == IPC_GFX_DRAW)
            fb_draw_pixel(msg.payload.gfx_draw.x, msg.payload.gfx_draw.y, msg.payload.gfx_draw.color);
        else if (msg.type == IPC_GFX_CURSOR_MOVE)
            update_cursor(msg.payload.cursor_move.dx, msg.payload.cursor_move.dy);
    }
}
