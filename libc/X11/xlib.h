#ifndef COREX_XLIB_H
#define COREX_XLIB_H

#include "../ipc/ipc.h"
#include <stdint.h>

// Data types (simplified)
typedef struct _XDisplay Display;
typedef uint32_t Window;
typedef uint32_t Drawable;
typedef uint32_t GC;
typedef uint32_t Colormap;

// Function declarations (simplified for demonstration)
Display* XOpenDisplay(const char* display_name);
int XCloseDisplay(Display* display);
Window XCreateSimpleWindow(Display* display, Window parent, int x, int y, unsigned int width, unsigned int height, unsigned int border_width, unsigned long border, unsigned long background);
int XMapWindow(Display* display, Window window);
int XFlush(Display* display);
GC XDefaultGC(Display* display, int screen_number);
int XFillRectangle(Display* display, Drawable d, GC gc, int x, int y, unsigned int width, unsigned int height);
Window XDefaultRootWindow(Display* display);

#endif
