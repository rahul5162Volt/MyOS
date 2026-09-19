#ifndef FONT_H
#define FONT_H

#include <stdint.h>
#include "font_layout.h"

#define FONT_CELL_WIDTH  6
#define FONT_CELL_HEIGHT 8

void font_draw_char(
    uint16_t x,
    uint16_t y,
    char character,
    uint32_t color
);

void font_draw_string(
    uint16_t x,
    uint16_t y,
    const char* text,
    uint32_t color
);

void font_draw_char_scaled(
    uint16_t x,
    uint16_t y,
    char character,
    uint32_t color,
    uint8_t scale
);

void font_draw_string_scaled(
    uint16_t x,
    uint16_t y,
    const char* text,
    uint32_t color,
    uint8_t scale
);

uint16_t font_string_width(
    const char* text,
    uint8_t scale
);

uint16_t font_string_height(
    const char* text,
    uint8_t scale
);

void font_draw_string_centered(
    uint16_t center_x,
    uint16_t y,
    const char* text,
    uint32_t color,
    uint8_t scale
);

void font_draw_string_right(
    uint16_t right_x,
    uint16_t y,
    const char* text,
    uint32_t color,
    uint8_t scale
);

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
);

#endif
