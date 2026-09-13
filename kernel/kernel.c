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

    __asm__ volatile (
        "mov %0, %%eax\n"
        "ud2\n"
        :
        : "m"(video->framebuffer)
        : "eax"
    );
    
    ui_init();

    vga_clear();
    vga_disable_cursor();
    fs_init();
    editor_init();

    ui_render();

    while (1)
    {
        if (keyboard_has_data())
        {
            unsigned char scancode;

            scancode = keyboard_read_scancode();

            keyboard_update_state(scancode);

            if (!keyboard_is_release(scancode))
            {
                editor_handle_key(scancode);
                ui_render();
            }
        }
    }
}
