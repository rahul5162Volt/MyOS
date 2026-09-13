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

#endif
