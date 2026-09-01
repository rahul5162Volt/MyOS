#ifndef UI_TEXT_H
#define UI_TEXT_H

typedef struct
{
    unsigned int row;
    unsigned int column;

    const char* text;

    unsigned char attribute;

    int visible;
} UI_Text;

void ui_text_init(
    UI_Text* text,
    unsigned int row,
    unsigned int column,
    const char* value,
    unsigned char attribute
);

void ui_text_render(
    const UI_Text* text
);

#endif