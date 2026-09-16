#ifndef UI_TEXT_H
#define UI_TEXT_H

#include "ui_color.h"

typedef struct
{
    unsigned int row;
    unsigned int column;

    const char* text;

    ui_color_t color;

    int visible;
} UI_Text;

void ui_text_init(
    UI_Text* text,
    unsigned int row,
    unsigned int column,
    const char* value,
    ui_color_t color
);

void ui_text_render(
    const UI_Text* text
);

#endif
