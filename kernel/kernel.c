#include "editor.h"
#include "editor_input.h"
#include "../editor/editor_undo.h"
#include "editor_render.h"
#include "keyboard/keyboard.h"

void kernel_main(void)
{
    editor_init();

    editor_insert_char('M');
    editor_insert_char('y');
    editor_insert_char('O');
    editor_insert_char('S');

    editor_insert_newline();

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
                editor_handle_key(scancode);
                editor_render();
            }
        }
    }
}
