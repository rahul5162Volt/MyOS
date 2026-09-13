#include "framebuffer.h"

static volatile uint8_t* framebuffer_address;
static uint16_t framebuffer_pitch;
static uint16_t framebuffer_width;
static uint16_t framebuffer_height;
static uint8_t framebuffer_bpp;

void framebuffer_init(
    uint32_t address,
    uint16_t pitch,
    uint16_t width,
    uint16_t height,
    uint8_t bpp
)
{
    framebuffer_address = (volatile uint8_t*)address;
    framebuffer_pitch = pitch;
    framebuffer_width = width;
    framebuffer_height = height;
    framebuffer_bpp = bpp;
}

void framebuffer_clear(uint32_t color)
{
    uint16_t y;
    uint16_t x;

    for (y = 0; y < framebuffer_height; y++)
    {
        for (x = 0; x < framebuffer_width; x++)
        {
            framebuffer_put_pixel(x, y, color);
        }
    }
}

void framebuffer_put_pixel(
    uint16_t x,
    uint16_t y,
    uint32_t color
)
{
    volatile uint32_t* pixel;

    if (x >= framebuffer_width || y >= framebuffer_height)
        return;

    if (framebuffer_bpp != 32)
        return;

    pixel = (volatile uint32_t*)
        (framebuffer_address + (y * framebuffer_pitch) + (x * 4));

    *pixel = color;
}
