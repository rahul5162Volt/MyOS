#ifndef UI_VIEWPORT_H
#define UI_VIEWPORT_H

#include "window.h"

typedef struct
{
    unsigned int row;
    unsigned int column;

    unsigned int width;
    unsigned int height;
} UI_Viewport;

void ui_viewport_init(
    UI_Viewport* viewport,
    unsigned int row,
    unsigned int column,
    unsigned int width,
    unsigned int height
);

void ui_viewport_from_window(
    UI_Viewport* viewport,
    const UI_Window* window
);

int ui_viewport_contains(
    const UI_Viewport* viewport,
    unsigned int row,
    unsigned int column
);

#endif
