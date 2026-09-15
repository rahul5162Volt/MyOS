#ifndef FONT_RENDER_H
#define FONT_RENDER_H

#include <stdint.h>

void font_render_char(
    uint16_t x,
    uint16_t y,
    char character,
    uint32_t color
);

void font_render_char_scaled(
    uint16_t x,
    uint16_t y,
    char character,
    uint32_t color,
    uint8_t scale
);

#endif
