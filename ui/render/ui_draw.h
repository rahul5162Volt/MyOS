#ifndef UI_DRAW_H
#define UI_DRAW_H

#include "ui_color.h"

unsigned int ui_draw_get_width(void);
unsigned int ui_draw_get_height(void);

void ui_draw_init(void);

void ui_draw_clear(void);

void ui_draw_cell(
    unsigned int row,
    unsigned int column,
    char character,
    ui_color_t color
);

void ui_draw_fill_rect(
    unsigned int row,
    unsigned int column,
    unsigned int width,
    unsigned int height,
    char character,
    ui_color_t color
);

#endif
