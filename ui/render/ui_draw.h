#ifndef UI_DRAW_H
#define UI_DRAW_H

#define UI_DRAW_WIDTH  80
#define UI_DRAW_HEIGHT 25

void ui_draw_clear(void);

void ui_draw_cell(
    unsigned int row,
    unsigned int column,
    char character,
    unsigned char attribute
);

#endif
