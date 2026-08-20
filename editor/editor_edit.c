#include "editor_edit.h"
#include "editor_state.h"
#include "editor_text.h"

void editor_insert_newline(void)
{
    EditorLine *current_line;
    EditorLine *next_line;

    unsigned int column;
    unsigned int move_count;

    if (editor_cursor_row >= EDITOR_MAX_LINES - 1)
        return;

    current_line =
        &editor_lines[editor_cursor_row];

    next_line =
        &editor_lines[editor_cursor_row + 1];

    /*
     * Move all lines below the current line
     * down by one.
     */
    move_count =
        EDITOR_MAX_LINES - 1;

    while (move_count > editor_cursor_row + 1)
    {
        editor_lines[move_count] =
            editor_lines[move_count - 1];

        move_count--;
    }

    /*
     * Re-acquire pointers because the array
     * contents have been shifted.
     */
    current_line =
        &editor_lines[editor_cursor_row];

    next_line =
        &editor_lines[editor_cursor_row + 1];

    /*
     * Move the text after the cursor to the
     * beginning of the new line.
     */
    column = editor_cursor_column;

    next_line->length = 0;

    while (column < current_line->length)
    {
        next_line->text[next_line->length] =
            current_line->text[column];

        next_line->length++;

        column++;
    }

    /*
     * Clear the moved characters from the
     * current line.
     */
    column = editor_cursor_column;

    while (column < current_line->length)
    {
        current_line->text[column] = ' ';
        column++;
    }

    /*
     * The current line is now explicitly
     * terminated by Enter.
     */
    current_line->length =
        editor_cursor_column;

    current_line->hard_break = 1;

    /*
     * The newly created line is not itself
     * terminated by Enter.
     */
    next_line->hard_break = 0;

    /*
     * Move cursor to the beginning of the
     * new line.
     */
    editor_cursor_row++;
    editor_cursor_column = 0;
    editor_preferred_column = 0;
}

void editor_delete_backward(void)
{
    EditorLine *line;
    unsigned int index;

    if (editor_cursor_row >= EDITOR_MAX_LINES)
        return;

    line =
        &editor_lines[editor_cursor_row];

    /*
     * Normal backspace inside the current line.
     */
    if (editor_cursor_column > 0)
    {
        index =
            editor_cursor_column - 1;

        while (index < line->length - 1)
        {
            line->text[index] =
                line->text[index + 1];

            index++;
        }

        line->length--;

        line->text[line->length] = ' ';

        editor_cursor_column--;

        editor_preferred_column =
            editor_cursor_column;

        return;
    }

    /*
     * At the beginning of the first line:
     * nothing to delete.
     */
    if (editor_cursor_row == 0)
        return;

    /*
     * Join this line with the previous line.
     */
    {
        EditorLine *previous_line =
            &editor_lines[
                editor_cursor_row - 1
            ];

        unsigned int previous_length =
            previous_line->length;

        /*
         * Only merge if the previous line was
         * separated by an actual Enter.
         */
        if (!previous_line->hard_break)
            return;

        /*
         * Make sure both lines fit together.
         */
        if (previous_length + line->length >
            EDITOR_MAX_COLUMNS)
        {
            return;
        }

        /*
         * Copy current line onto the end of
         * the previous line.
         */
        index = 0;

        while (index < line->length)
        {
            previous_line->text[
                previous_length + index
            ] =
                line->text[index];

            index++;
        }

        previous_line->length =
            previous_length + line->length;

        /*
         * The previous line is no longer separated
         * from this line by Enter.
         */
        previous_line->hard_break = 0;

        /*
         * Move cursor to the old end of the
         * previous line.
         */
        editor_cursor_row--;

        editor_cursor_column =
            previous_length;

        editor_preferred_column =
            editor_cursor_column;

        /*
         * Clear the now-unused current line.
         */
        line->length = 0;
        line->hard_break = 0;

        index = 0;

        while (index < EDITOR_MAX_COLUMNS)
        {
            line->text[index] = ' ';
            index++;
        }
    }
}

void editor_delete_forward(void)
{
    EditorLine *line;
    unsigned int index;

    if (editor_cursor_row >= EDITOR_MAX_LINES)
        return;

    line =
        &editor_lines[editor_cursor_row];

    /*
     * Delete the character at the cursor.
     */
    if (editor_cursor_column < line->length)
    {
        index = editor_cursor_column;

        while (index < line->length - 1)
        {
            line->text[index] =
                line->text[index + 1];

            index++;
        }

        line->length--;

        line->text[line->length] = ' ';

        return;
    }

    /*
     * At the end of the current line.
     *
     * If this line has a following logical line,
     * merge that line into the current line.
     */
    if (editor_cursor_column == line->length &&
        editor_cursor_row < EDITOR_MAX_LINES - 1)
    {
        EditorLine *next_line =
            &editor_lines[
                editor_cursor_row + 1
            ];

        unsigned int current_length =
            line->length;

        /*
         * Only merge when the current line
         * actually ends with Enter.
         */
        if (!line->hard_break)
            return;

        /*
         * Make sure both lines fit.
         */
        if (current_length + next_line->length >
            EDITOR_MAX_COLUMNS)
        {
            return;
        }

        /*
         * Append the next line.
         */
        index = 0;

        while (index < next_line->length)
        {
            line->text[
                current_length + index
            ] =
                next_line->text[index];

            index++;
        }

        line->length =
            current_length + next_line->length;

        /*
         * The newline between the two lines
         * has been deleted.
         */
        line->hard_break =
            next_line->hard_break;

        /*
         * Remove the now-unused line.
         */
        next_line->length = 0;
        next_line->hard_break = 0;

        index = 0;

        while (index < EDITOR_MAX_COLUMNS)
        {
            next_line->text[index] = ' ';
            index++;
        }
    }
}

void editor_insert_tab(void)
{
    unsigned int spaces = 4;
    unsigned int count = 0;

    while (count < spaces)
    {
        editor_insert_char(' ');
        count++;
    }
}
