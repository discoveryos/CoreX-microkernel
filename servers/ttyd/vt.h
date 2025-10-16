#ifndef VT_H
#define VT_H

// Initialize all virtual terminals
void init_vt_system();

// Switch to a specific virtual terminal (e.g., Ctrl+Alt+F1–F6)
void switch_vt(int vt_id);

// Draw the contents of a virtual terminal to the framebuffer
void draw_vt(int vt_id);

// Save the current framebuffer state into a VT buffer
void save_vt(int vt_id);

#endif#ifndef VT_H
#define VT_H

// Initialize all virtual terminals
void init_vt_system();

// Switch to a specific virtual terminal (e.g., Ctrl+Alt+F1–F6)
void switch_vt(int vt_id);

// Draw the contents of a virtual terminal to the framebuffer
void draw_vt(int vt_id);

// Save the current framebuffer state into a VT buffer
void save_vt(int vt_id);

#endif
