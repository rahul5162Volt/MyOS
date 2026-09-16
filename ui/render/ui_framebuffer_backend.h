#ifndef UI_FRAMEBUFFER_BACKEND_H
#define UI_FRAMEBUFFER_BACKEND_H

#include "ui_color.h"

void ui_framebuffer_backend_init(void);

void ui_framebuffer_backend_clear(void);

void ui_framebuffer_backend_draw_cell(
    unsigned int row,
    unsigned int column,
    char character,
    ui_color_t color
);

unsigned int ui_framebuffer_backend_get_width(void);
unsigned int ui_framebuffer_backend_get_height(void);

#endif
