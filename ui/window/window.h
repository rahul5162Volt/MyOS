#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include "ui_color.h"

typedef struct
{
    unsigned int row;
    unsigned int column;
    unsigned int width;
    unsigned int height;

    const char* title;

    ui_color_t border_color;
    ui_color_t title_color;

} UI_Window;

void ui_window_init(
    UI_Window* window,
    unsigned int row,
    unsigned int column,
    unsigned int width,
    unsigned int height,
    const char* title,
    ui_color_t border_color,
    ui_color_t title_color
);

void ui_window_render(
    const UI_Window* window
);

unsigned int ui_window_content_row(
    const UI_Window* window
);

unsigned int ui_window_content_column(
    const UI_Window* window
);

unsigned int ui_window_content_width(
    const UI_Window* window
);

unsigned int ui_window_content_height(
    const UI_Window* window
);

#endif
