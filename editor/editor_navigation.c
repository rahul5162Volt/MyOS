#include "editor_navigation.h"
#include "editor_state.h"

void editor_cursor_left(void)
{
    EditorLine *previous_line;

    if (editor_cursor_row >= EDITOR_MAX_LINES)
        return;

    /*
     * Move normally inside the current line.
     */
    if (editor_cursor_column > 0)
    {
        editor_cursor_column--;

        editor_preferred_column =
            editor_cursor_column;

        return;
    }

    /*
     * At column 0.
     */
    if (editor_cursor_row == 0)
        return;

    previous_line =
        &editor_lines[editor_cursor_row - 1];

    /*
     * Cross the line boundary only when
     * the previous line was explicitly terminated
     * with Enter.
     */
    if (previous_line->hard_break == 0)
        return;

    editor_cursor_row--;

    /*
     * Position at the actual end of the previous
     * line's text.
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
     * Normal movement within the line.
     */
    if (editor_cursor_column < line->length)
    {
        editor_cursor_column++;

        editor_preferred_column =
            editor_cursor_column;

        return;
    }

    /*
     * At the end of the line.
     * Cross to the next line only when
     * this line ends with Enter.
     */
    if (editor_cursor_column == line->length &&
        editor_cursor_row < EDITOR_MAX_LINES - 1 &&
        line->hard_break)
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
