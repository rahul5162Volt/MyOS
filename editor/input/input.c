#include "state.h"
#include "edit.h"
#include "selection.h"
#include "cursor.h"
#include "text.h"
#include "clipboard.h"
#include "undo.h"
#include "keyboard/keyboard.h"

void editor_handle_key(unsigned char scancode)
{
    if (keyboard_is_arrow_left(scancode) ||
        keyboard_is_arrow_right(scancode) ||
        keyboard_is_arrow_up(scancode) ||
        keyboard_is_arrow_down(scancode) ||
        keyboard_is_enter(scancode) ||
        keyboard_is_backspace(scancode) ||
        keyboard_is_delete(scancode) ||
        keyboard_is_tab(scancode) ||
        keyboard_is_home(scancode) ||
        keyboard_is_end(scancode))
    {
        editor_undo_group_active = 0;
    }
    if (keyboard_is_ctrl_pressed() &&
        scancode == 0x2C)
    {
        if (editor_undo_can_undo())
            editor_undo();

        return;
    }
    if (keyboard_is_ctrl_pressed() &&
        scancode == 0x15)
    {
        if (editor_undo_can_redo())
            editor_redo();

        return;
    }
    if (keyboard_is_ctrl_pressed() &&
        scancode == 0x2E)
    {
        editor_clipboard_copy_selection();

        return;
    }
    if (keyboard_is_ctrl_pressed() &&
        scancode == 0x2D)
    {
        if (editor_selection_is_active())
            editor_undo_save();

        editor_clipboard_cut_selection();

        return;
    }
    if (keyboard_is_ctrl_pressed() &&
        scancode == 0x2F)
    {
        if (editor_clipboard_has_data())
            editor_undo_save();

        editor_clipboard_paste();

        return;
    }
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
        editor_undo_save();

        if (editor_selection_is_active())
            editor_selection_delete();

        editor_insert_newline();

        return;
    }

    if (keyboard_is_ctrl_pressed() &&
        keyboard_is_backspace(scancode))
    {
        editor_undo_group_active = 0;

        editor_undo_save();

        if (editor_selection_is_active())
            editor_selection_delete();
        else
            editor_delete_word_backward();

        return;
    }

    if (keyboard_is_backspace(scancode))
    {
        editor_undo_save();

        if (editor_selection_is_active())
            editor_selection_delete();
        else
            editor_delete_backward();

        return;
    }

    if (keyboard_is_ctrl_pressed() &&
        keyboard_is_delete(scancode))
    {
        editor_undo_group_active = 0;

        editor_undo_save();

        if (editor_selection_is_active())
            editor_selection_delete();
        else
            editor_delete_word_forward();

        return;
    }

    if (keyboard_is_delete(scancode))
    {
        editor_undo_save();

        if (editor_selection_is_active())
            editor_selection_delete();
        else
            editor_delete_forward();

        return;
    }

    if (keyboard_is_tab(scancode))
    {
        editor_undo_save();
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
            /*
            * Start a new undo group when typing begins.
            */
            if (!editor_undo_group_active)
            {
                editor_undo_save();

                editor_undo_group_active = 1;

                editor_undo_group_row =
                    editor_cursor_row;

                editor_undo_group_column =
                    editor_cursor_column;
            }

            if (editor_selection_is_active())
            {
                editor_selection_delete();

                /*
                * Selection deletion is a separate editing
                * operation, so restart the typing group.
                */
                editor_undo_group_active = 0;

                editor_undo_save();

                editor_undo_group_active = 1;

                editor_undo_group_row =
                    editor_cursor_row;

                editor_undo_group_column =
                    editor_cursor_column;
            }

            editor_insert_char(character);
        }
    }
}
