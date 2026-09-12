#ifndef UI_BACKEND_H
#define UI_BACKEND_H

void ui_backend_clear(void);

void ui_backend_draw_cell(
    unsigned int row,
    unsigned int column,
    char character,
    unsigned char attribute
);

#endif
