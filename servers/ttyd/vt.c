#include "framebuffer.h"
#include "vt.h"

#define MAX_VT 6
#define VT_WIDTH 80
#define VT_HEIGHT 25

static char vt_buffers[MAX_VT][VT_WIDTH * VT_HEIGHT];
static int active_vt = 0;

void init_vt_system() {
    for (int i = 0; i < MAX_VT; i++) {
        memset(vt_buffers[i], ' ', VT_WIDTH * VT_HEIGHT);
    }
    draw_vt(active_vt);
}

void switch_vt(int vt_id) {
    if (vt_id < 0 || vt_id >= MAX_VT) return;
    save_vt(active_vt);
    active_vt = vt_id;
    draw_vt(active_vt);
}

void draw_vt(int vt_id) {
    for (int i = 0; i < VT_WIDTH * VT_HEIGHT; i++) {
        int x = i % VT_WIDTH;
        int y = i / VT_WIDTH;
        fb_draw_char(x * 8, y * 16, vt_buffers[vt_id][i], 0xFFFFFF);
    }
}

void save_vt(int vt_id) {
    // Optional: capture current framebuffer text state
}
