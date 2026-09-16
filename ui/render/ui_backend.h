#ifndef UI_BACKEND_H
#define UI_BACKEND_H

#include "ui_color.h"

void ui_backend_init(void);

void ui_backend_clear(void);

void ui_backend_draw_cell(
    unsigned int row,
    unsigned int column,
    char character,
    ui_color_t color
);

#endif
