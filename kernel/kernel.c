#include "video/renderer.h"
#include "video/video_info.h"

void kernel_main(void)
{
    video_info_t* video =
        (video_info_t*)VIDEO_INFO_ADDRESS;

    renderer_init(
        video->framebuffer,
        video->pitch,
        video->width,
        video->height,
        video->bpp
    );

    renderer_clear(0x00000000);

    renderer_fill_rect(
        100,
        100,
        300,
        150,
        0x00FF0000
    );

    renderer_draw_rect(
        500,
        100,
        300,
        150,
        0x0000FF00
    );

    renderer_draw_line(
        100,
        400,
        900,
        600,
        0x000000FF
    );

    renderer_fill_circle(
        512,
        384,
        100,
        0x00FFFF00
    );

    renderer_draw_circle(
        512,
        384,
        160,
        0x00FFFFFF
    );

    renderer_fill_triangle(
        350,
        500,
        512,
        300,
        674,
        500,
        0x0000FFFF
    );

    while (1)
    {
        __asm__ volatile ("hlt");
    }
}
