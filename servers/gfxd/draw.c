#include "framebuffer.h"

void draw_pixel(int x, int y, uint32_t color) {
    fb_draw_pixel(x, y, color);
}

void draw_rect(int x, int y, int w, int h, uint32_t color) {
    for (int dy = 0; dy < h; dy++) {
        for (int dx = 0; dx < w; dx++) {
            draw_pixel(x + dx, y + dy, color);
        }
    }
}
