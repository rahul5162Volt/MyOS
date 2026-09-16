#include "ui_backend.h"
#include "ui_framebuffer_backend.h"

void ui_backend_init(void)
{
    ui_framebuffer_backend_init();
}

void ui_backend_clear(void)
{
    ui_framebuffer_backend_clear();
}

void ui_backend_draw_cell(
    unsigned int row,
    unsigned int column,
    char character,
    ui_color_t color
)
{
    ui_framebuffer_backend_draw_cell(
        row,
        column,
        character,
        color
    );
}
