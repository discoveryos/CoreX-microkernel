#include "doomgeneric.h"
#include <stdint.h>

// A buffer to hold the 320x200 pixel data.
static uint32_t screen_buffer[DG_SCREEN_WIDTH * DG_SCREEN_HEIGHT];

void DG_Init() {
    // Set the global pointer so Doom knows where to render.
    DG_ScreenBuffer = screen_buffer;

    // Initialize your kernel's graphics driver.
    // E.g., set up a VGA framebuffer or similar.
    // kernel_graphics_init();
}

void DG_DrawFrame() {
    // Copy the contents of the `screen_buffer` to your kernel's actual screen.
    // This is where you would call your kernel's drawing function.
    // For example, if you have a `kernel_blit` function:
    // kernel_blit(screen_buffer, DG_SCREEN_WIDTH, DG_SCREEN_HEIGHT);
}

void DG_SleepMs(uint32_t ms) {
    // Call your kernel's sleep or delay function.
    // For example:
    // kernel_delay(ms);
}

uint32_t DG_GetTicksMs() {
    // Return the number of milliseconds since boot.
    // This would require a timer interrupt handler in your kernel.
    // return kernel_get_uptime_ms();
    return 0; // Placeholder
}

void DG_GetKey(int* key, int* pressed) {
    // Poll your kernel's keyboard driver for events.
    // For example, using a queue or interrupt handler.
    // *key = kernel_get_key();
    // *pressed = kernel_is_key_pressed();
    *key = 0; // Placeholder
    *pressed = 0; // Placeholder
}

void DG_SetWindowTitle(const char* title) {
    // Not needed for a kernel port without a window manager.
    (void)title;
}


