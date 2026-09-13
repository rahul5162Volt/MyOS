#include "ui_draw.h"
#include "ui_backend.h"

void ui_draw_clear(void)
{
    ui_backend_clear();
}

void ui_draw_cell(
    unsigned int row,
    unsigned int column,
    char character,
    unsigned char attribute
)
{
    ui_backend_draw_cell(
        row,
        column,
        character,
        attribute
    );
}

void ui_draw_fill_rect(
    unsigned int row,
    unsigned int column,
    unsigned int width,
    unsigned int height,
    char character,
    unsigned char attribute
)
{
    unsigned int y;
    unsigned int x;

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            ui_draw_cell(
                row + y,
                column + x,
                character,
                attribute
            );
        }
    }
}
