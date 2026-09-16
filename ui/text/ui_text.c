#include "ui_text.h"
#include "ui_draw.h"

void ui_text_init(
    UI_Text* text,
    unsigned int row,
    unsigned int column,
    const char* value,
    ui_color_t color
)
{
    text->row = row;
    text->column = column;
    text->text = value;
    text->color = color;
    text->visible = 1;
}

void ui_text_render(
    const UI_Text* text
)
{
    unsigned int column;
    const char* value;

    if (!text->visible)
    {
        return;
    }

    column = text->column;
    value = text->text;

    if (value == 0)
    {
        return;
    }

    while (*value != '\0' &&
           column < ui_draw_get_width())
    {
        ui_draw_cell(
            text->row,
            column,
            *value,
            text->color
        );

        column++;
        value++;
    }
}
