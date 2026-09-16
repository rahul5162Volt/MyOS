#ifndef UI_LAYOUT_H
#define UI_LAYOUT_H

#include "ui_color.h"

typedef struct
{
    unsigned int row;
    unsigned int column;
    unsigned int width;
    unsigned int height;

    char character;
    ui_color_t color;

    int visible;

} UI_Panel;

void ui_panel_init(
    UI_Panel* panel,
    unsigned int row,
    unsigned int column,
    unsigned int width,
    unsigned int height,
    char character,
    ui_color_t color
);

void ui_panel_render(
    const UI_Panel* panel
);

#endif
