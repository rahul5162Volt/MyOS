#include "font.h"
#include "font_render.h"

void font_draw_char(
    uint16_t x,
    uint16_t y,
    char character,
    uint32_t color
)
{
    font_render_char(
        x,
        y,
        character,
        color
    );
}

void font_draw_char_scaled(
    uint16_t x,
    uint16_t y,
    char character,
    uint32_t color,
    uint8_t scale
)
{
    font_render_char_scaled(
        x,
        y,
        character,
        color,
        scale
    );
}
