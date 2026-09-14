#include "renderer.h"
#include "framebuffer.h"

void renderer_init(
    uint32_t address,
    uint16_t pitch,
    uint16_t width,
    uint16_t height,
    uint8_t bpp
)
{
    framebuffer_init(
        address,
        pitch,
        width,
        height,
        bpp
    );
}

void renderer_clear(uint32_t color)
{
    framebuffer_clear(color);
}

void renderer_fill_rect(
    uint16_t x,
    uint16_t y,
    uint16_t width,
    uint16_t height,
    uint32_t color
)
{
    framebuffer_fill_rect(x, y, width, height, color);
}

void renderer_draw_rect(
    uint16_t x,
    uint16_t y,
    uint16_t width,
    uint16_t height,
    uint32_t color
)
{
    framebuffer_draw_rect(x, y, width, height, color);
}

void renderer_draw_line(
    uint16_t x1,
    uint16_t y1,
    uint16_t x2,
    uint16_t y2,
    uint32_t color
)
{
    framebuffer_draw_line(x1, y1, x2, y2, color);
}

void renderer_fill_circle(
    uint16_t center_x,
    uint16_t center_y,
    uint16_t radius,
    uint32_t color
)
{
    framebuffer_fill_circle(center_x, center_y, radius, color);
}

void renderer_draw_circle(
    uint16_t center_x,
    uint16_t center_y,
    uint16_t radius,
    uint32_t color
)
{
    int32_t x = radius;
    int32_t y = 0;
    int32_t decision = 1 - radius;

    while (x >= y)
    {
        framebuffer_put_pixel(center_x + x, center_y + y, color);
        framebuffer_put_pixel(center_x + y, center_y + x, color);
        framebuffer_put_pixel(center_x - y, center_y + x, color);
        framebuffer_put_pixel(center_x - x, center_y + y, color);
        framebuffer_put_pixel(center_x - x, center_y - y, color);
        framebuffer_put_pixel(center_x - y, center_y - x, color);
        framebuffer_put_pixel(center_x + y, center_y - x, color);
        framebuffer_put_pixel(center_x + x, center_y - y, color);

        y++;

        if (decision <= 0)
        {
            decision += 2 * y + 1;
        }
        else
        {
            x--;
            decision += 2 * (y - x) + 1;
        }
    }
}

void renderer_fill_triangle(
    uint16_t x1,
    uint16_t y1,
    uint16_t x2,
    uint16_t y2,
    uint16_t x3,
    uint16_t y3,
    uint32_t color
)
{
    int32_t min_x = x1;
    int32_t max_x = x1;
    int32_t min_y = y1;
    int32_t max_y = y1;
    int32_t x;
    int32_t y;

    if (x2 < min_x)
        min_x = x2;

    if (x3 < min_x)
        min_x = x3;

    if (x2 > max_x)
        max_x = x2;

    if (x3 > max_x)
        max_x = x3;

    if (y2 < min_y)
        min_y = y2;

    if (y3 < min_y)
        min_y = y3;

    if (y2 > max_y)
        max_y = y2;

    if (y3 > max_y)
        max_y = y3;

    for (y = min_y; y <= max_y; y++)
    {
        for (x = min_x; x <= max_x; x++)
        {
            int32_t edge1 =
                (x2 - x1) * (y - y1) -
                (y2 - y1) * (x - x1);

            int32_t edge2 =
                (x3 - x2) * (y - y2) -
                (y3 - y2) * (x - x2);

            int32_t edge3 =
                (x1 - x3) * (y - y3) -
                (y1 - y3) * (x - x3);

            if ((edge1 >= 0 && edge2 >= 0 && edge3 >= 0) ||
                (edge1 <= 0 && edge2 <= 0 && edge3 <= 0))
            {
                if (x >= 0 && y >= 0)
                {
                    framebuffer_put_pixel(
                        (uint16_t)x,
                        (uint16_t)y,
                        color
                    );
                }
            }
        }
    }
}
