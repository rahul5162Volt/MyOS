#include "ui_text.h"
#include "vga.h"

void ui_text_init(
    UI_Text* text,
    unsigned int row,
    unsigned int column,
    const char* value,
    unsigned char attribute
)
{
    text->row = row;
    text->column = column;

    text->text = value;

    text->attribute = attribute;

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
           column < VGA_WIDTH)
    {
        vga_write_cell(
            text->row,
            column,
            *value,
            text->attribute
        );

        column++;
        value++;
    }
}
