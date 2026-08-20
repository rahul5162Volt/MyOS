#include "editor_input.h"

#include "editor_edit.h"
#include "editor_selection.h"
#include "editor_cursor.h"
#include "editor_text.h"
#include "keyboard/keyboard.h"

void editor_handle_key(unsigned char scancode)
{
    if (keyboard_is_ctrl_pressed() &&
        scancode == 0x1E)
    {
        editor_selection_all();

        return;
    }
    if (keyboard_is_ctrl_pressed() &&
        keyboard_is_shift_pressed() &&
        keyboard_is_arrow_left(scancode))
    {
        if (!editor_selection_has_anchor())
            editor_selection_start();

        editor_cursor_word_left();
        editor_selection_update();

        return;
    }

    if (keyboard_is_ctrl_pressed() &&
        keyboard_is_shift_pressed() &&
        keyboard_is_arrow_right(scancode))
    {
        if (!editor_selection_has_anchor())
            editor_selection_start();

        editor_cursor_word_right();
        editor_selection_update();

        return;
    }
    
    if (keyboard_is_shift_pressed() &&
        keyboard_is_arrow_left(scancode))
    {
        if (!editor_selection_has_anchor())
            editor_selection_start();

        editor_cursor_left();
        editor_selection_update();

        return;
    }

    if (keyboard_is_shift_pressed() &&
        keyboard_is_arrow_right(scancode))
    {
        if (!editor_selection_has_anchor())
            editor_selection_start();

        editor_cursor_right();
        editor_selection_update();

        return;
    }

    if (keyboard_is_shift_pressed() &&
        keyboard_is_arrow_up(scancode))
    {
        if (!editor_selection_has_anchor())
            editor_selection_start();

        editor_cursor_up();
        editor_selection_update();

        return;
    }

    if (keyboard_is_shift_pressed() &&
        keyboard_is_arrow_down(scancode))
    {
        if (!editor_selection_has_anchor())
            editor_selection_start();

        editor_cursor_down();
        editor_selection_update();

        return;
    }

    if (keyboard_is_ctrl_pressed() &&
        keyboard_is_arrow_left(scancode))
    {
        editor_selection_clear();
        editor_cursor_word_left();

        return;
    }

    if (keyboard_is_ctrl_pressed() &&
        keyboard_is_arrow_right(scancode))
    {
        editor_selection_clear();
        editor_cursor_word_right();

        return;
    }

    if (keyboard_is_arrow_left(scancode))
    {
        editor_selection_clear();
        editor_cursor_left();

        return;
    }

    if (keyboard_is_arrow_right(scancode))
    {
        editor_selection_clear();
        editor_cursor_right();

        return;
    }

    if (keyboard_is_arrow_up(scancode))
    {
        editor_selection_clear();
        editor_cursor_up();

        return;
    }

    if (keyboard_is_arrow_down(scancode))
    {
        editor_selection_clear();
        editor_cursor_down();

        return;
    }

    if (keyboard_is_enter(scancode))
    {
        if (editor_selection_is_active())
            editor_selection_delete();

        editor_insert_newline();

        return;
    }

    if (keyboard_is_backspace(scancode))
    {
        if (editor_selection_is_active())
            editor_selection_delete();
        else
            editor_delete_backward();

        return;
    }

    if (keyboard_is_delete(scancode))
    {
        if (editor_selection_is_active())
            editor_selection_delete();
        else
            editor_delete_forward();

        return;
    }

    if (keyboard_is_tab(scancode))
    {
        editor_insert_tab();

        return;
    }

    if (keyboard_is_ctrl_pressed() &&
        keyboard_is_shift_pressed() &&
        keyboard_is_home(scancode))
    {
        if (!editor_selection_has_anchor())
            editor_selection_start();

        editor_selection_to_document_start();

        return;
    }

    if (keyboard_is_ctrl_pressed() &&
        keyboard_is_shift_pressed() &&
        keyboard_is_end(scancode))
    {
        if (!editor_selection_has_anchor())
            editor_selection_start();

        editor_selection_to_document_end();

        return;
    }

    if (keyboard_is_home(scancode))
    {
        if (keyboard_is_shift_pressed())
        {
            if (!editor_selection_has_anchor())
                editor_selection_start();

            editor_selection_to_home();
        }
        else
        {
            editor_selection_clear();
            editor_cursor_home();
        }

        return;
    }

    if (keyboard_is_end(scancode))
    {
        if (keyboard_is_shift_pressed())
        {
            if (!editor_selection_has_anchor())
                editor_selection_start();

            editor_selection_to_end();
        }
        else
        {
            editor_selection_clear();
            editor_cursor_end();
        }

        return;
    }

    {
        char character =
            keyboard_scancode_to_ascii(scancode);

        if (character != '\0')
        {
            if (editor_selection_is_active())
                editor_selection_delete();

            editor_insert_char(character);
        }
    }
}
