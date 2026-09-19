#include "os_menu_input.h"

#include "keyboard/keyboard.h"
#include "application_manager.h"

void os_menu_input_run(void)
{
    while (1)
    {
        if (keyboard_has_data())
        {
            unsigned char scancode =
                keyboard_read_scancode();

            char key =
                keyboard_scancode_to_ascii(scancode);

            keyboard_update_state(scancode);

            if (!keyboard_is_release(scancode))
            {
                if (key == '1')
                {
                    os_application_manager_run_editor();
                    return;
                }

                if (key == '2')
                {
                    os_application_manager_run_calculator();
                    return;
                }
            }
        }
    }
}
