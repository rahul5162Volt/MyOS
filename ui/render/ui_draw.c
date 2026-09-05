#include "ui_draw.h"
#include "vga.h"

void ui_draw_clear(void)
{
    vga_clear();
}

void ui_draw_cell(
    unsigned int row,
    unsigned int column,
    char character,
    unsigned char attribute
)
{
    vga_write_cell(
        row,
        column,
        character,
        attribute
    );
}
