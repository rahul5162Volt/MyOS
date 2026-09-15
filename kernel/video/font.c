#include "font.h"
#include "framebuffer.h"

static const uint8_t font_digits[10][7] =
{
    {0x0E, 0x11, 0x13, 0x15, 0x19, 0x11, 0x0E},
    {0x04, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x0E},
    {0x0E, 0x11, 0x01, 0x02, 0x04, 0x08, 0x1F},
    {0x1F, 0x02, 0x04, 0x02, 0x01, 0x11, 0x0E},
    {0x02, 0x06, 0x0A, 0x12, 0x1F, 0x02, 0x02},
    {0x1F, 0x10, 0x1E, 0x01, 0x01, 0x11, 0x0E},
    {0x06, 0x08, 0x10, 0x1E, 0x11, 0x11, 0x0E},
    {0x1F, 0x01, 0x02, 0x04, 0x08, 0x08, 0x08},
    {0x0E, 0x11, 0x11, 0x0E, 0x11, 0x11, 0x0E},
    {0x0E, 0x11, 0x11, 0x0F, 0x01, 0x02, 0x0C}
};

static const uint8_t font_uppercase[26][7] =
{
    {0x0E, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11},
    {0x1E, 0x11, 0x11, 0x1E, 0x11, 0x11, 0x1E},
    {0x0E, 0x11, 0x10, 0x10, 0x10, 0x11, 0x0E},
    {0x1E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1E},
    {0x1F, 0x10, 0x10, 0x1E, 0x10, 0x10, 0x1F},
    {0x1F, 0x10, 0x10, 0x1E, 0x10, 0x10, 0x10},
    {0x0E, 0x11, 0x10, 0x17, 0x11, 0x11, 0x0F},
    {0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11},
    {0x0E, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0E},
    {0x07, 0x02, 0x02, 0x02, 0x12, 0x12, 0x0C},
    {0x11, 0x12, 0x14, 0x18, 0x14, 0x12, 0x11},
    {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F},
    {0x11, 0x1B, 0x15, 0x15, 0x11, 0x11, 0x11},
    {0x11, 0x19, 0x19, 0x15, 0x13, 0x13, 0x11},
    {0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E},
    {0x1E, 0x11, 0x11, 0x1E, 0x10, 0x10, 0x10},
    {0x0E, 0x11, 0x11, 0x11, 0x15, 0x12, 0x0D},
    {0x1E, 0x11, 0x11, 0x1E, 0x14, 0x12, 0x11},
    {0x0F, 0x10, 0x10, 0x0E, 0x01, 0x01, 0x1E},
    {0x1F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E},
    {0x11, 0x11, 0x11, 0x11, 0x11, 0x0A, 0x04},
    {0x11, 0x11, 0x11, 0x15, 0x15, 0x1B, 0x11},
    {0x11, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x11},
    {0x11, 0x11, 0x0A, 0x04, 0x04, 0x04, 0x04},
    {0x1F, 0x01, 0x02, 0x04, 0x08, 0x10, 0x1F}
};

static const uint8_t font_lowercase[26][7] =
{
    {0x00, 0x00, 0x0E, 0x01, 0x0F, 0x11, 0x0F}, /* a */
    {0x10, 0x10, 0x1E, 0x11, 0x11, 0x11, 0x1E}, /* b */
    {0x00, 0x00, 0x0E, 0x10, 0x10, 0x10, 0x0E}, /* c */
    {0x01, 0x01, 0x0F, 0x11, 0x11, 0x11, 0x0F}, /* d */
    {0x00, 0x00, 0x0E, 0x11, 0x1F, 0x10, 0x0E}, /* e */
    {0x06, 0x09, 0x08, 0x1E, 0x08, 0x08, 0x08}, /* f */
    {0x00, 0x00, 0x0F, 0x11, 0x0F, 0x01, 0x0E}, /* g */
    {0x10, 0x10, 0x16, 0x19, 0x11, 0x11, 0x11}, /* h */
    {0x04, 0x00, 0x0C, 0x04, 0x04, 0x04, 0x0E}, /* i */
    {0x02, 0x00, 0x06, 0x02, 0x02, 0x12, 0x0C}, /* j */
    {0x10, 0x10, 0x12, 0x14, 0x18, 0x14, 0x12}, /* k */
    {0x0C, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0E}, /* l */
    {0x00, 0x00, 0x1A, 0x15, 0x15, 0x15, 0x11}, /* m */
    {0x00, 0x00, 0x16, 0x19, 0x11, 0x11, 0x11}, /* n */
    {0x00, 0x00, 0x0E, 0x11, 0x11, 0x11, 0x0E}, /* o */
    {0x00, 0x00, 0x1E, 0x11, 0x1E, 0x10, 0x10}, /* p */
    {0x00, 0x00, 0x0F, 0x11, 0x0F, 0x01, 0x01}, /* q */
    {0x00, 0x00, 0x16, 0x19, 0x10, 0x10, 0x10}, /* r */
    {0x00, 0x00, 0x0F, 0x10, 0x0E, 0x01, 0x1E}, /* s */
    {0x08, 0x08, 0x1E, 0x08, 0x08, 0x09, 0x06}, /* t */
    {0x00, 0x00, 0x11, 0x11, 0x11, 0x13, 0x0D}, /* u */
    {0x00, 0x00, 0x11, 0x11, 0x11, 0x0A, 0x04}, /* v */
    {0x00, 0x00, 0x11, 0x15, 0x15, 0x15, 0x0A}, /* w */
    {0x00, 0x00, 0x11, 0x0A, 0x04, 0x0A, 0x11}, /* x */
    {0x00, 0x00, 0x11, 0x11, 0x0F, 0x01, 0x0E}, /* y */
    {0x00, 0x00, 0x1F, 0x02, 0x04, 0x08, 0x1F}  /* z */
};

static const uint8_t font_punctuation[][7] =
{
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C}, /* . */
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x08}, /* , */
    {0x04, 0x04, 0x04, 0x04, 0x00, 0x04, 0x04}, /* ! */
    {0x0E, 0x11, 0x01, 0x02, 0x04, 0x00, 0x04}, /* ? */
    {0x00, 0x04, 0x00, 0x00, 0x04, 0x04, 0x08}, /* : */
    {0x00, 0x04, 0x00, 0x04, 0x04, 0x08, 0x00}, /* ; */
    {0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00}, /* - */
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F}  /* _ */
};

void font_draw_char(
    uint16_t x,
    uint16_t y,
    char character,
    uint32_t color
)
{
    const uint8_t* glyph;
    uint8_t row;
    uint8_t column;

    if (character >= '0' && character <= '9')
    {
        glyph = font_digits[character - '0'];
    }
    else if (character >= 'A' && character <= 'Z')
    {
        glyph = font_uppercase[character - 'A'];
    }
    else if (character >= 'a' && character <= 'z')
    {
        glyph = font_lowercase[character - 'a'];
    }
    else if (character == ' ')
    {
        return;
    }
    else if (character == '.' ||
            character == ',' ||
            character == '!' ||
            character == '?' ||
            character == ':' ||
            character == ';' ||
            character == '-' ||
            character == '_')
    {
        uint8_t punctuation_index = 0;

        switch (character)
        {
            case '.': punctuation_index = 0; break;
            case ',': punctuation_index = 1; break;
            case '!': punctuation_index = 2; break;
            case '?': punctuation_index = 3; break;
            case ':': punctuation_index = 4; break;
            case ';': punctuation_index = 5; break;
            case '-': punctuation_index = 6; break;
            case '_': punctuation_index = 7; break;
        }

        glyph = font_punctuation[punctuation_index];
    }
    else
    {
        return;
    }

    for (row = 0; row < 7; row++)
    {
        for (column = 0; column < 5; column++)
        {
            if (glyph[row] & (1 << (4 - column)))
            {
                framebuffer_put_pixel(
                    x + column,
                    y + row,
                    color
                );
            }
        }
    }
}

void font_draw_char_scaled(
    uint16_t x,
    uint16_t y,
    char character,
    uint32_t color,
    uint8_t scale
)
{
    const uint8_t* glyph;
    uint8_t row;
    uint8_t column;

    if (scale == 0)
        return;

    if (character >= '0' && character <= '9')
    {
        glyph = font_digits[character - '0'];
    }
    else if (character >= 'A' && character <= 'Z')
    {
        glyph = font_uppercase[character - 'A'];
    }
    else if (character >= 'a' && character <= 'z')
    {
        glyph = font_lowercase[character - 'a'];
    }
    else if (character == ' ')
    {
        return;
    }
    else if (character == '.' ||
             character == ',' ||
             character == '!' ||
             character == '?' ||
             character == ':' ||
             character == ';' ||
             character == '-' ||
             character == '_')
    {
        uint8_t punctuation_index = 0;

        switch (character)
        {
            case '.': punctuation_index = 0; break;
            case ',': punctuation_index = 1; break;
            case '!': punctuation_index = 2; break;
            case '?': punctuation_index = 3; break;
            case ':': punctuation_index = 4; break;
            case ';': punctuation_index = 5; break;
            case '-': punctuation_index = 6; break;
            case '_': punctuation_index = 7; break;
        }

        glyph = font_punctuation[punctuation_index];
    }
    else
    {
        return;
    }

    for (row = 0; row < 7; row++)
    {
        for (column = 0; column < 5; column++)
        {
            if (glyph[row] & (1 << (4 - column)))
            {
                uint8_t scale_y;
                uint8_t scale_x;

                for (scale_y = 0; scale_y < scale; scale_y++)
                {
                    for (scale_x = 0; scale_x < scale; scale_x++)
                    {
                        framebuffer_put_pixel(
                            x + (column * scale) + scale_x,
                            y + (row * scale) + scale_y,
                            color
                        );
                    }
                }
            }
        }
    }
}

void font_draw_string(
    uint16_t x,
    uint16_t y,
    const char* text,
    uint32_t color
)
{
    uint16_t start_x = x;

    while (*text)
    {
        if (*text == '\n')
        {
            x = start_x;
            y += 8;
        }
        else
        {
            font_draw_char(x, y, *text, color);
            x += 6;
        }

        text++;
    }
}

void font_draw_string_scaled(
    uint16_t x,
    uint16_t y,
    const char* text,
    uint32_t color,
    uint8_t scale
)
{
    uint16_t start_x = x;
    uint16_t advance;
    uint16_t line_height;

    if (scale == 0)
        return;

    advance = 6 * scale;
    line_height = 8 * scale;

    while (*text)
    {
        if (*text == '\n')
        {
            x = start_x;
            y += line_height;
        }
        else
        {
            font_draw_char_scaled(
                x,
                y,
                *text,
                color,
                scale
            );

            x += advance;
        }

        text++;
    }
}

uint16_t font_string_width(
    const char* text,
    uint8_t scale
)
{
    uint16_t width = 0;
    uint16_t current_width = 0;
    uint16_t advance;

    if (scale == 0)
        return 0;

    advance = 6 * scale;

    while (*text)
    {
        if (*text == '\n')
        {
            if (current_width > width)
                width = current_width;

            current_width = 0;
        }
        else
        {
            current_width += advance;
        }

        text++;
    }

    if (current_width > width)
        width = current_width;

    if (width > 0)
        width -= scale;

    return width;
}

uint16_t font_string_height(
    const char* text,
    uint8_t scale
)
{
    uint16_t lines = 1;

    if (scale == 0)
        return 0;

    while (*text)
    {
        if (*text == '\n')
            lines++;

        text++;
    }

    return lines * 7 * scale;
}

void font_draw_string_centered(
    uint16_t center_x,
    uint16_t y,
    const char* text,
    uint32_t color,
    uint8_t scale
)
{
    uint16_t width;
    uint16_t x;

    if (scale == 0)
        return;

    width = font_string_width(text, scale);

    if (width >= center_x * 2)
        x = 0;
    else
        x = center_x - (width / 2);

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
    uint16_t width;
    uint16_t x;

    if (scale == 0)
        return;

    width = font_string_width(text, scale);

    if (width >= right_x)
        x = 0;
    else
        x = right_x - width;

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
    uint16_t text_width;
    uint16_t text_height;
    uint16_t draw_x;
    uint16_t draw_y;

    if (scale == 0)
        return;

    text_width = font_string_width(text, scale);
    text_height = font_string_height(text, scale);

    if (horizontal_alignment == FONT_ALIGN_CENTER)
    {
        if (text_width >= width)
            draw_x = x;
        else
            draw_x = x + ((width - text_width) / 2);
    }
    else if (horizontal_alignment == FONT_ALIGN_RIGHT)
    {
        if (text_width >= width)
            draw_x = x;
        else
            draw_x = x + width - text_width;
    }
    else
    {
        draw_x = x;
    }

    if (vertical_alignment == FONT_ALIGN_MIDDLE)
    {
        if (text_height >= height)
            draw_y = y;
        else
            draw_y = y + ((height - text_height) / 2);
    }
    else if (vertical_alignment == FONT_ALIGN_BOTTOM)
    {
        if (text_height >= height)
            draw_y = y;
        else
            draw_y = y + height - text_height;
    }
    else
    {
        draw_y = y;
    }

    font_draw_string_scaled(
        draw_x,
        draw_y,
        text,
        color,
        scale
    );
}
