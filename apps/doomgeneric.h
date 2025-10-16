#ifndef __DOOMGENERIC_H__
#define __DOOMGENERIC_H__

#include <stdint.h>

// Screen dimensions. The DOOM engine expects 320x200 pixel resolution.
#define DG_SCREEN_WIDTH 320
#define DG_SCREEN_HEIGHT 200

// This is the framebuffer where DOOM renders its output.
// Your platform-specific code needs to copy the contents of this buffer
// to the actual screen on every frame.
extern uint32_t* DG_ScreenBuffer;

// ---- Required functions to implement in doomgeneric_yourplatform.c ----

// Initialize your platform. This includes setting up the framebuffer,
// keyboard, and timer.
void DG_Init();

// Called by DOOM to render the current frame. You should copy
// `DG_ScreenBuffer` to your screen device here.
void DG_DrawFrame();

// Sleep for a given number of milliseconds.
void DG_SleepMs(uint32_t ms);

// Get the number of milliseconds since your platform was initialized.
uint32_t DG_GetTicksMs();

// Provide keyboard events to DOOM. Your function should fill `*key` and `*pressed`.
// `*pressed` is 1 for a key down event and 0 for a key up event.
void DG_GetKey(int* key, int* pressed);

// ---- Optional functions ----

// Set the window title. Not required for a kernel port.
void DG_SetWindowTitle(const char* title);

// ---- Main Doom entry point ----

// Create the Doom instance with command-line arguments.
void doomgeneric_Create(int argc, char** argv);

// The main loop function for Doom. Your platform should call this repeatedly.
void doomgeneric_Tick();

#endif // __DOOMGENERIC_H__
