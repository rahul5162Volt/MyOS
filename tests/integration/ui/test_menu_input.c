#include "test_menu_input.h"

#include "keyboard/keyboard.h"
#include "ui_draw.h"

void ui_test_menu_input(void)
{
    while (1)
    {
        if (keyboard_has_data())
        {
            unsigned char scancode =
                keyboard_read_scancode();

            keyboard_update_state(scancode);

            if (!keyboard_is_release(scancode))
            {
                if (keyboard_scancode_to_ascii(scancode) == '1')
                {
                    ui_draw_clear();
                    return;
                }
            }
        }
    }
}
