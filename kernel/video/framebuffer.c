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

void framebuffer_fill_rect(
    uint16_t x,
    uint16_t y,
    uint16_t width,
    uint16_t height,
    uint32_t color
)
{
    uint32_t right;
    uint32_t bottom;
    uint16_t xx;
    uint16_t yy;

    if (width == 0 || height == 0)
        return;

    right = (uint32_t)x + width;
    bottom = (uint32_t)y + height;

    if (x >= framebuffer_width || y >= framebuffer_height)
        return;

    if (right > framebuffer_width)
        right = framebuffer_width;

    if (bottom > framebuffer_height)
        bottom = framebuffer_height;

    for (yy = y; yy < bottom; yy++)
    {
        for (xx = x; xx < right; xx++)
        {
            framebuffer_put_pixel(xx, yy, color);
        }
    }
}

void framebuffer_draw_rect(
    uint16_t x,
    uint16_t y,
    uint16_t width,
    uint16_t height,
    uint32_t color
)
{
    uint32_t right;
    uint32_t bottom;
    uint16_t xx;
    uint16_t yy;

    if (width == 0 || height == 0)
        return;

    if (x >= framebuffer_width || y >= framebuffer_height)
        return;

    right = (uint32_t)x + width;
    bottom = (uint32_t)y + height;

    if (right > framebuffer_width)
        right = framebuffer_width;

    if (bottom > framebuffer_height)
        bottom = framebuffer_height;

    for (xx = x; xx < right; xx++)
    {
        framebuffer_put_pixel(xx, y, color);

        if (bottom > y + 1)
            framebuffer_put_pixel(xx, bottom - 1, color);
    }

    for (yy = y; yy < bottom; yy++)
    {
        framebuffer_put_pixel(x, yy, color);

        if (right > x + 1)
            framebuffer_put_pixel(right - 1, yy, color);
    }
}

void framebuffer_draw_line(
    uint16_t x1,
    uint16_t y1,
    uint16_t x2,
    uint16_t y2,
    uint32_t color
)
{
    int32_t dx = (int32_t)x2 - x1;
    int32_t dy = (int32_t)y2 - y1;

    int32_t sx = (dx >= 0) ? 1 : -1;
    int32_t sy = (dy >= 0) ? 1 : -1;

    dx = (dx >= 0) ? dx : -dx;
    dy = (dy >= 0) ? dy : -dy;

    int32_t err = dx - dy;

    while (1)
    {
        framebuffer_put_pixel(x1, y1, color);

        if (x1 == x2 && y1 == y2)
            break;

        int32_t e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void framebuffer_fill_circle(
    uint16_t center_x,
    uint16_t center_y,
    uint16_t radius,
    uint32_t color
)
{
    int32_t radius_squared = (int32_t)radius * radius;
    int32_t y;

    for (y = -(int32_t)radius; y <= (int32_t)radius; y++)
    {
        int32_t x;
        int32_t y_squared = y * y;

        for (x = -(int32_t)radius; x <= (int32_t)radius; x++)
        {
            if ((x * x) + y_squared <= radius_squared)
            {
                int32_t pixel_x = (int32_t)center_x + x;
                int32_t pixel_y = (int32_t)center_y + y;

                if (pixel_x >= 0 && pixel_y >= 0 &&
                    pixel_x < framebuffer_width &&
                    pixel_y < framebuffer_height)
                {
                    framebuffer_put_pixel(
                        (uint16_t)pixel_x,
                        (uint16_t)pixel_y,
                        color
                    );
                }
            }
        }
    }
}
