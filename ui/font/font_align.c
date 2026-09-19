#include "font_align.h"
#include "font_layout.h"

void font_draw_string_centered(
    uint16_t center_x,
    uint16_t y,
    const char* text,
    uint32_t color,
    uint8_t scale
)
{
    uint16_t width =
        font_string_width(text, scale);

    uint16_t x =
        center_x - (width / 2);

    font_draw_string_scaled(
        x,
        y,
        text,
        color,
        scale
    );
}

void font_draw_string_right(
    uint16_t right_x,
    uint16_t y,
    const char* text,
    uint32_t color,
    uint8_t scale
)
{
    uint16_t width =
        font_string_width(text, scale);

    uint16_t x =
        right_x - width;

    font_draw_string_scaled(
        x,
        y,
        text,
        color,
        scale
    );
}

void font_draw_string_in_rect(
    uint16_t x,
    uint16_t y,
    uint16_t width,
    uint16_t height,
    const char* text,
    uint32_t color,
    uint8_t scale,
    uint8_t horizontal_alignment,
    uint8_t vertical_alignment
)
{
    uint16_t text_width =
        font_string_width(text, scale);

    uint16_t text_height =
        font_string_height(text, scale);

    uint16_t draw_x = x;
    uint16_t draw_y = y;

    if (horizontal_alignment == FONT_ALIGN_CENTER)
    {
        if (text_width < width)
            draw_x = x + ((width - text_width) / 2);
    }
    else if (horizontal_alignment == FONT_ALIGN_RIGHT)
    {
        if (text_width < width)
            draw_x = x + width - text_width;
    }

    if (vertical_alignment == FONT_ALIGN_MIDDLE)
    {
        if (text_height < height)
            draw_y = y + ((height - text_height) / 2);
    }
    else if (vertical_alignment == FONT_ALIGN_BOTTOM)
    {
        if (text_height < height)
            draw_y = y + height - text_height;
    }

    font_draw_string_scaled(
        draw_x,
        draw_y,
        text,
        color,
        scale
    );
}
