#include "framebuffer.h"

static int cursor_x = 400;
static int cursor_y = 300;
static uint32_t cursor_color = 0xFFFFFF;

void draw_cursor() {
    fb_draw_pixel(cursor_x, cursor_y, cursor_color);         // center
    fb_draw_pixel(cursor_x - 1, cursor_y, cursor_color);     // left
    fb_draw_pixel(cursor_x + 1, cursor_y, cursor_color);     // right
    fb_draw_pixel(cursor_x, cursor_y - 1, cursor_color);     // up
    fb_draw_pixel(cursor_x, cursor_y + 1, cursor_color);     // down
}

void erase_cursor() {
    fb_draw_pixel(cursor_x, cursor_y, 0x000000);
    fb_draw_pixel(cursor_x - 1, cursor_y, 0x000000);
    fb_draw_pixel(cursor_x + 1, cursor_y, 0x000000);
    fb_draw_pixel(cursor_x, cursor_y - 1, 0x000000);
    fb_draw_pixel(cursor_x, cursor_y + 1, 0x000000);
}

void update_cursor(int dx, int dy) {
    erase_cursor();
    cursor_x += dx;
    cursor_y += dy;
    draw_cursor();
}#include "framebuffer.h"

static int cursor_x = 400;
static int cursor_y = 300;
static uint32_t cursor_color = 0xFFFFFF;

void draw_cursor() {
    fb_draw_pixel(cursor_x, cursor_y, cursor_color);         // center
    fb_draw_pixel(cursor_x - 1, cursor_y, cursor_color);     // left
    fb_draw_pixel(cursor_x + 1, cursor_y, cursor_color);     // right
    fb_draw_pixel(cursor_x, cursor_y - 1, cursor_color);     // up
    fb_draw_pixel(cursor_x, cursor_y + 1, cursor_color);     // down
}

void erase_cursor() {
    fb_draw_pixel(cursor_x, cursor_y, 0x000000);
    fb_draw_pixel(cursor_x - 1, cursor_y, 0x000000);
    fb_draw_pixel(cursor_x + 1, cursor_y, 0x000000);
    fb_draw_pixel(cursor_x, cursor_y - 1, 0x000000);
    fb_draw_pixel(cursor_x, cursor_y + 1, 0x000000);
}

void update_cursor(int dx, int dy) {
    erase_cursor();
    cursor_x += dx;
    cursor_y += dy;
    draw_cursor();
}
