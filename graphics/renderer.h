#ifndef RENDERER_H
#define RENDERER_H

#include <stdint.h>

void renderer_init(
    uint32_t address,
    uint16_t pitch,
    uint16_t width,
    uint16_t height,
    uint8_t bpp
);

void renderer_clear(uint32_t color);

void renderer_fill_rect(
    uint16_t x,
    uint16_t y,
    uint16_t width,
    uint16_t height,
    uint32_t color
);

void renderer_draw_rect(
    uint16_t x,
    uint16_t y,
    uint16_t width,
    uint16_t height,
    uint32_t color
);

void renderer_draw_line(
    uint16_t x1,
    uint16_t y1,
    uint16_t x2,
    uint16_t y2,
    uint32_t color
);

void renderer_fill_circle(
    uint16_t center_x,
    uint16_t center_y,
    uint16_t radius,
    uint32_t color
);

void renderer_draw_circle(
    uint16_t center_x,
    uint16_t center_y,
    uint16_t radius,
    uint32_t color
);

void renderer_fill_triangle(
    uint16_t x1,
    uint16_t y1,
    uint16_t x2,
    uint16_t y2,
    uint16_t x3,
    uint16_t y3,
    uint32_t color
);

#endif
