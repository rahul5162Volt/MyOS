#include "font_layout.h"
#include "font_render.h"

static uint16_t font_char_width(uint8_t scale)
{
    return 5 * scale;
}

static uint16_t font_char_height(uint8_t scale)
{
    return 7 * scale;
}

static uint16_t font_char_spacing(uint8_t scale)
{
    return scale;
}

void font_draw_string(
    uint16_t x,
    uint16_t y,
    const char* text,
    uint32_t color
)
{
    font_draw_string_scaled(
        x,
        y,
        text,
        color,
        1
    );
}

void font_draw_string_scaled(
    uint16_t x,
    uint16_t y,
    const char* text,
    uint32_t color,
    uint8_t scale
)
{
    uint16_t cursor_x = x;
    uint16_t cursor_y = y;

    uint16_t advance =
        font_char_width(scale) +
        font_char_spacing(scale);

    uint16_t line_height =
        font_char_height(scale) +
        font_char_spacing(scale);

    while (*text)
    {
        if (*text == '\n')
        {
            cursor_x = x;
            cursor_y += line_height;
            text++;
            continue;
        }

        font_render_char_scaled(
            cursor_x,
            cursor_y,
            *text,
            color,
            scale
        );

        cursor_x += advance;
        text++;
    }
}

uint16_t font_string_width(
    const char* text,
    uint8_t scale
)
{
    uint16_t current_width = 0;
    uint16_t max_width = 0;

    uint16_t advance =
        font_char_width(scale) +
        font_char_spacing(scale);

    while (*text)
    {
        if (*text == '\n')
        {
            if (current_width > max_width)
                max_width = current_width;

            current_width = 0;
            text++;
            continue;
        }

        current_width += advance;
        text++;
    }

    if (current_width > max_width)
        max_width = current_width;

    if (max_width > 0)
        max_width -= font_char_spacing(scale);

    return max_width;
}

uint16_t font_string_height(
    const char* text,
    uint8_t scale
)
{
    uint16_t lines = 1;

    while (*text)
    {
        if (*text == '\n')
            lines++;

        text++;
    }

    return
        (lines * font_char_height(scale)) +
        ((lines - 1) * font_char_spacing(scale));
}
