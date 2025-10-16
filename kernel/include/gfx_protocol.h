#ifndef GFX_PROTOCOL_H
#define GFX_PROTOCOL_H
#include <stdint.h>
#define GFX_CMD_DRAW_CIRCLE 3
typedef struct { int request_type; int x; int y; int radius; uint32_t color; } gfx_request_t;
#endif
