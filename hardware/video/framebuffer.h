#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>

void framebuffer_init(
    uint32_t address,
    uint16_t pitch,
    uint16_t width,
    uint16_t height,
    uint8_t bpp
);

void framebuffer_clear(uint32_t color);

void framebuffer_put_pixel(
    uint16_t x,
    uint16_t y,
    uint32_t color
);

void framebuffer_fill_rect(
    uint16_t x,
    uint16_t y,
    uint16_t width,
    uint16_t height,
    uint32_t color
);

void framebuffer_draw_rect(
    uint16_t x,
    uint16_t y,
    uint16_t width,
    uint16_t height,
    uint32_t color
);

void framebuffer_draw_line(
    uint16_t x1,
    uint16_t y1,
    uint16_t x2,
    uint16_t y2,
    uint32_t color
);

void framebuffer_fill_circle(
    uint16_t center_x,
    uint16_t center_y,
    uint16_t radius,
    uint32_t color
);

#endif
