#include <stdint.h>
#include <math.h>

volatile uint16_t *vga_buffer = (volatile uint16_t*)0xB8000;
uint32_t width = 80;
uint32_t height = 25;

void terminal_writestring(const char* str) {
    uint32_t i = 0;
    uint32_t col = 0;
    while(str[i] != '\0') {
        vga_buffer[col] = (uint16_t)str[i] | 0x0F00;
        i++;
        col++;
    }
}

void terminal_clear() {
    for (uint32_t i = 0; i < width * height; i++) {
        vga_buffer[i] = ' ' | 0x0F00;
    }
}

void draw_pixel(uint32_t x, uint32_t y, uint32_t color) {
    uint32_t *fb = (uint32_t*)0xA0000000; // Conceptual framebuffer base
    if (x < width && y < height) {
        fb[y * width + x] = color;
    }
}

void draw_circle_points(int xc, int yc, int x, int y, uint32_t color) {
    draw_pixel(xc + x, yc + y, color);
    draw_pixel(xc - x, yc + y, color);
    draw_pixel(xc + x, yc - y, color);
    draw_pixel(xc - x, yc - y, color);
    draw_pixel(xc + y, yc + x, color);
    draw_pixel(xc - y, yc + x, color);
    draw_pixel(xc + y, yc - x, color);
    draw_pixel(xc - y, yc - x, color);
}

void draw_circle(int xc, int yc, int radius, uint32_t color) {
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;
    
    while (x <= y) {
        draw_circle_points(xc, yc, x, y, color);
        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}
