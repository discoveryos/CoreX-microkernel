#ifndef _FRAMEBUFFER_H
#define _FRAMEBUFFER_H

#include <stdint.h>
#include <stddef.h>

/**
 * @brief Represents the physical framebuffer memory and its properties.
 *
 * This structure holds essential information about the display, including
 * its dimensions, color depth, and a pointer to the video memory.
 */
typedef struct framebuffer {
    uint32_t width;        ///< The width of the framebuffer in pixels.
    uint32_t height;       ///< The height of the framebuffer in pixels.
    uint32_t pitch;        ///< The number of bytes per horizontal line.
    uint16_t bits_per_pixel; ///< The number of bits per pixel.
    uint32_t *address;     ///< A pointer to the video memory.
} framebuffer_t;

/**
 * @brief Initializes the framebuffer and fills the provided structure.
 *
 * This function should be called once during kernel initialization.
 * It will discover the video mode and populate the framebuffer_t structure.
 *
 * @param fb A pointer to the framebuffer structure to be filled.
 * @return 0 on success, or a negative value on failure.
 */
int framebuffer_init(framebuffer_t *fb);

/**
 * @brief Clears the entire framebuffer to a specific color.
 *
 * @param fb A pointer to the framebuffer structure.
 * @param color The color to fill the screen with.
 */
void framebuffer_clear(framebuffer_t *fb, uint32_t color);

/**
 * @brief Sets the color of a single pixel.
 *
 * @param fb A pointer to the framebuffer structure.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color value for the pixel.
 */
void framebuffer_put_pixel(framebuffer_t *fb, uint32_t x, uint32_t y, uint32_t color);

/**
 * @brief Blits a rectangular area of pixel data to the framebuffer.
 *
 * This function is optimized for copying large blocks of pixel data,
 * which is a primary function for displaying the Doom screen.
 *
 * @param fb A pointer to the framebuffer structure.
 * @param x The x-coordinate of the top-left corner.
 * @param y The y-coordinate of the top-left corner.
 * @param width The width of the area to copy.
 * @param height The height of the area to copy.
 * @param data A pointer to the source pixel data.
 */
void framebuffer_blit(framebuffer_t *fb, uint32_t x, uint32_t y, uint32_t width, uint32_t height, const uint32_t *data);

#endif // _FRAMEBUFFER_H
