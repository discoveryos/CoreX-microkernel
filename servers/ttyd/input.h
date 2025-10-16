#ifndef _INPUT_H
#define _INPUT_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Enumeration of standard keyboard key codes.
 * 
 * These codes are high-level, device-independent representations of keys,
 * which is what the Doom engine's input routines expect.
 * Note: These should be mapped from raw hardware scan codes in the driver.
 */
typedef enum {
    KEY_NONE = 0,
    KEY_ESCAPE = 1,
    KEY_1 = 2,
    KEY_2 = 3,
    KEY_3 = 4,
    KEY_4 = 5,
    KEY_5 = 6,
    KEY_6 = 7,
    KEY_7 = 8,
    KEY_8 = 9,
    KEY_9 = 10,
    KEY_0 = 11,
    KEY_MINUS = 12,
    KEY_EQUALS = 13,
    KEY_BACKSPACE = 14,
    KEY_TAB = 15,
    KEY_Q = 16,
    KEY_W = 17,
    KEY_E = 18,
    KEY_R = 19,
    KEY_T = 20,
    KEY_Y = 21,
    KEY_U = 22,
    KEY_I = 23,
    KEY_O = 24,
    KEY_P = 25,
    KEY_ENTER = 28,
    KEY_LCTRL = 29,
    KEY_A = 30,
    KEY_S = 31,
    KEY_D = 32,
    KEY_F = 33,
    KEY_G = 34,
    KEY_H = 35,
    KEY_J = 36,
    KEY_K = 37,
    KEY_L = 38,
    KEY_LSHIFT = 42,
    KEY_Z = 44,
    KEY_X = 45,
    KEY_C = 46,
    KEY_V = 47,
    KEY_B = 48,
    KEY_N = 49,
    KEY_M = 50,
    KEY_COMMA = 51,
    KEY_DOT = 52,
    KEY_SLASH = 53,
    KEY_RSHIFT = 54,
    KEY_KP_STAR = 55, // Numpad *
    KEY_LALT = 56,
    KEY_SPACE = 57,
    KEY_CAPSLOCK = 58,
    KEY_F1 = 59,
    KEY_F2 = 60,
    KEY_F3 = 61,
    KEY_F4 = 62,
    KEY_F5 = 63,
    KEY_F6 = 64,
    KEY_F7 = 65,
    KEY_F8 = 66,
    KEY_F9 = 67,
    KEY_F10 = 68,
    KEY_NUMLOCK = 69,
    KEY_SCROLLLOCK = 70,
    KEY_HOME = 71,
    KEY_UP = 72,
    KEY_PGUP = 73,
    KEY_LEFT = 75,
    KEY_RIGHT = 77,
    KEY_END = 79,
    KEY_DOWN = 80,
    KEY_PGDN = 81,
    KEY_INSERT = 82,
    KEY_DELETE = 83,
    KEY_F11 = 87,
    KEY_F12 = 88,
    KEY_RCTRL = 97,
    KEY_RALT = 100,
    // Add more keys as needed...
} key_t;

/**
 * @brief Initializes the keyboard driver.
 *
 * This function should set up the necessary interrupt handlers and hardware.
 */
void input_init_keyboard();

/**
 * @brief Checks if a specific key is currently pressed.
 * 
 * @param key The key to check.
 * @return True if the key is pressed, false otherwise.
 */
bool input_is_key_pressed(key_t key);

/**
 * @brief Gets the next pending key event from the input queue.
 * 
 * This function is used to retrieve key presses and releases in a polling loop.
 * 
 * @param key A pointer to store the key code of the event.
 * @param pressed A pointer to a boolean indicating if it was a press (true) or release (false).
 * @return True if an event was available, false otherwise.
 */
bool input_get_key_event(key_t *key, bool *pressed);

#endif // _INPUT_H
