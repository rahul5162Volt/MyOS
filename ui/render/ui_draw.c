#include "ui_draw.h"
#include "ui_backend.h"
#include "ui_framebuffer_backend.h"

unsigned int ui_draw_get_width(void)
{
    return ui_framebuffer_backend_get_width();
}

unsigned int ui_draw_get_height(void)
{
    return ui_framebuffer_backend_get_height();
}

void ui_draw_init(void)
{
    ui_backend_init();
}

void ui_draw_clear(void)
{
    ui_backend_clear();
}

void ui_draw_cell(
    unsigned int row,
    unsigned int column,
    char character,
    ui_color_t color
)
{
    ui_backend_draw_cell(
        row,
        column,
        character,
        color
    );
}

void ui_draw_fill_rect(
    unsigned int row,
    unsigned int column,
    unsigned int width,
    unsigned int height,
    char character,
    ui_color_t color
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
                color
            );
        }
    }
}
