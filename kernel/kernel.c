#include "keyboard/keyboard.h"
#include "vga/vga.h"
#include "editor.h"
#include "fs.h"

void kernel_main(void)
{
    vga_clear();

    fs_init();
    editor_init();
    editor_render();

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
                editor_render();
            }
        }
    }
}


