#include "editor.h"
#include "keyboard/keyboard.h"

void kernel_main(void)
{
    editor_init();

    editor_insert_char('M');
    editor_insert_char('y');
    editor_insert_char('O');
    editor_insert_char('S');

    editor_newline();

    editor_insert_char('E');
    editor_insert_char('d');
    editor_insert_char('i');
    editor_insert_char('t');
    editor_insert_char('o');
    editor_insert_char('r');

    editor_render();

    while (1)
    {
        if (keyboard_has_data())
        {
            unsigned char scancode =
                keyboard_read_scancode();

            keyboard_update_state(scancode);

            if (!keyboard_is_release(scancode))
            {
                if (keyboard_is_arrow_left(scancode))
                {
                    editor_cursor_left();
                    editor_render();
                }
                else if (keyboard_is_arrow_right(scancode))
                {
                    editor_cursor_right();
                    editor_render();
                }
                else if (keyboard_is_arrow_up(scancode))
                {
                    editor_cursor_up();
                    editor_render();
                }
                else if (keyboard_is_arrow_down(scancode))
                {
                    editor_cursor_down();
                    editor_render();
                }
                else if (keyboard_is_enter(scancode))
                {
                    editor_newline();
                    editor_render();
                }
                else if (keyboard_is_backspace(scancode))
                {
                    editor_backspace();
                    editor_render();
                }
                else
                {
                    char character =
                        keyboard_scancode_to_ascii(
                            scancode
                        );

                    if (character != '\0')
                    {
                        editor_insert_char(character);
                        editor_render();
                    }
                }
            }
        }
    }
}
