#include "font_render.h"
#include "font_data.h"
#include "framebuffer.h"

static const uint8_t* font_get_glyph(char character)
{
    if (character >= '0' && character <= '9')
        return font_digits[character - '0'];

    if (character >= 'A' && character <= 'Z')
        return font_uppercase[character - 'A'];

    if (character >= 'a' && character <= 'z')
        return font_lowercase[character - 'a'];

    if (character == ' ')
        return 0;

    if (character == '.' ||
        character == ',' ||
        character == '!' ||
        character == '?' ||
        character == ':' ||
        character == ';' ||
        character == '-' ||
        character == '_')
    {
        switch (character)
        {
            case '.': return font_punctuation[0];
            case ',': return font_punctuation[1];
            case '!': return font_punctuation[2];
            case '?': return font_punctuation[3];
            case ':': return font_punctuation[4];
            case ';': return font_punctuation[5];
            case '-': return font_punctuation[6];
            case '_': return font_punctuation[7];
        }
    }

    return 0;
}

static void font_draw_glyph(
    uint16_t x,
    uint16_t y,
    const uint8_t* glyph,
    uint32_t color,
    uint8_t scale
)
{
    uint8_t row;
    uint8_t column;

    if (!glyph || scale == 0)
        return;

    for (row = 0; row < 7; row++)
    {
        for (column = 0; column < 5; column++)
        {
            if (glyph[row] & (1 << (4 - column)))
            {
                uint8_t sy;
                uint8_t sx;

                for (sy = 0; sy < scale; sy++)
                {
                    for (sx = 0; sx < scale; sx++)
                    {
                        framebuffer_put_pixel(
                            x + (column * scale) + sx,
                            y + (row * scale) + sy,
                            color
                        );
                    }
                }
            }
        }
    }
}

void font_render_char(
    uint16_t x,
    uint16_t y,
    char character,
    uint32_t color
)
{
    const uint8_t* glyph = font_get_glyph(character);

    font_draw_glyph(
        x,
        y,
        glyph,
        color,
        1
    );
}

void font_render_char_scaled(
    uint16_t x,
    uint16_t y,
    char character,
    uint32_t color,
    uint8_t scale
)
{
    const uint8_t* glyph = font_get_glyph(character);

    font_draw_glyph(
        x,
        y,
        glyph,
        color,
        scale
    );
}
