#include "keyboard/keyboard.h"
#include "vga/vga.h"
#include "ui.h"
#include "editor.h"
#include "fs.h"
#include "video/framebuffer.h"
#include "video/video_info.h"

void kernel_main(void)
{
    video_info_t* video =
        (video_info_t*)VIDEO_INFO_ADDRESS;

    framebuffer_init(
        video->framebuffer,
        video->pitch,
        video->width,
        video->height,
        video->bpp
    );

    framebuffer_put_pixel(0, 0, 0x00FF0000);
    framebuffer_put_pixel(1, 0, 0x00FF0000);
    framebuffer_put_pixel(2, 0, 0x00FF0000);
    framebuffer_put_pixel(3, 0, 0x00FF0000);
    framebuffer_put_pixel(4, 0, 0x00FF0000);

    while (1)
    {
        __asm__ volatile ("hlt");
    }
}
