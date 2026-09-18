#include "editor.h"

#include "ui.h"
#include "keyboard/keyboard.h"
#include "input.h"
#include "application_runtime.h"

void editor_run(void)
{
    ui_init();
    ui_render();

    while (!application_should_exit())
    {
        if (keyboard_has_data())
        {
            unsigned char scancode =
                keyboard_read_scancode();

            keyboard_update_state(scancode);

            if (!keyboard_is_release(scancode))
            {
                if (scancode == 0x01)
                {
                    application_exit();
                    continue;
                }

                editor_handle_key(scancode);
                ui_render();
            }
        }
    }
}
