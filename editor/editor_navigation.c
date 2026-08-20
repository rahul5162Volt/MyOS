#include "editor_navigation.h"
#include "editor_state.h"

void editor_cursor_left(void)
{
    EditorLine *previous_line;

    if (editor_cursor_row >= EDITOR_MAX_LINES)
        return;

    /*
     * Move inside the current line.
     */
    if (editor_cursor_column > 0)
    {
        editor_cursor_column--;

        editor_preferred_column =
            editor_cursor_column;

        return;
    }

    /*
     * Already at the beginning of the first line.
     */
    if (editor_cursor_row == 0)
        return;

    previous_line =
        &editor_lines[editor_cursor_row - 1];

    /*
     * Only cross the line boundary when
     * Enter created that boundary.
     */
    if (!previous_line->hard_break)
        return;

    editor_cursor_row--;

    /*
     * Put the cursor at the actual end of
     * the previous line.
     */
    editor_cursor_column =
        previous_line->length;

    editor_preferred_column =
        editor_cursor_column;
}

void editor_cursor_right(void)
{
    EditorLine *line;

    if (editor_cursor_row >= EDITOR_MAX_LINES)
        return;

    line =
        &editor_lines[editor_cursor_row];

    /*
     * Move through the actual text.
     */
    if (editor_cursor_column < line->length)
    {
        editor_cursor_column++;

        editor_preferred_column =
            editor_cursor_column;

        return;
    }

    /*
     * At the logical end of the line.
     *
     * Cross only when Enter actually
     * separates this line from the next.
     */
    if (line->hard_break &&
        editor_cursor_row < EDITOR_MAX_LINES - 1)
    {
        editor_cursor_row++;
        editor_cursor_column = 0;
        editor_preferred_column = 0;
    }
}

void editor_cursor_up(void)
{
    EditorLine *line;
    unsigned int target_column;

    if (editor_cursor_row == 0)
        return;

    /*
     * Remember the column the user wants to maintain
     * while moving vertically.
     */
    target_column =
        editor_preferred_column;

    editor_cursor_row--;

    line =
        &editor_lines[editor_cursor_row];

    if (target_column > line->length)
        target_column = line->length;

    editor_cursor_column =
        target_column;
}

void editor_cursor_down(void)
{
    EditorLine *line;
    unsigned int target_column;

    if (editor_cursor_row >= EDITOR_MAX_LINES - 1)
        return;

    target_column =
        editor_preferred_column;

    editor_cursor_row++;

    line =
        &editor_lines[editor_cursor_row];

    if (target_column > line->length)
        target_column = line->length;

    editor_cursor_column =
        target_column;
}
