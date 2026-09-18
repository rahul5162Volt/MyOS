#include "test_editor.h"

#include "ui.h"
#include "keyboard/keyboard.h"
#include "input.h"

void ui_test_editor(void)
{
    ui_init();
    ui_render();

    while (1)
    {
        if (keyboard_has_data())
        {
            unsigned char scancode =
                keyboard_read_scancode();

            keyboard_update_state(scancode);

            if (!keyboard_is_release(scancode))
            {
                editor_handle_key(scancode);
                ui_render();
            }
        }
    }
}
