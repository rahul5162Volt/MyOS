#include "keyboard/keyboard.h"
#include "vga/vga.h"
#include "ui.h"
#include "editor.h"
#include "fs.h"

void kernel_main(void)
{
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
