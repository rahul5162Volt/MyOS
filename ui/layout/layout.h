#ifndef UI_LAYOUT_H
#define UI_LAYOUT_H

typedef struct
{
    unsigned int row;
    unsigned int column;

    unsigned int width;
    unsigned int height;

    unsigned char attribute;

    int visible;
} UI_Panel;

void ui_panel_init(
    UI_Panel* panel,
    unsigned int row,
    unsigned int column,
    unsigned int width,
    unsigned int height,
    unsigned char attribute
);

void ui_panel_render(
    const UI_Panel* panel
);

#endif
