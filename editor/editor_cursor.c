#include "editor_cursor.h"
#include "editor_state.h"

unsigned int editor_get_cursor_row(void)
{
    return editor_cursor_row;
}

unsigned int editor_get_cursor_column(void)
{
    return editor_cursor_column;
}

unsigned int editor_get_preferred_column(void)
{
    return editor_preferred_column;
}

void editor_set_cursor(
    unsigned int row,
    unsigned int column
)
{
    if (row >= EDITOR_MAX_LINES)
        row = EDITOR_MAX_LINES - 1;

    if (column >= EDITOR_MAX_COLUMNS)
        column = EDITOR_MAX_COLUMNS - 1;

    editor_cursor_row = row;
    editor_cursor_column = column;
}

void editor_set_preferred_column(unsigned int column)
{
    if (column >= EDITOR_MAX_COLUMNS)
        column = EDITOR_MAX_COLUMNS - 1;

    editor_preferred_column = column;
}

void editor_cursor_home(void)
{
    if (editor_cursor_row >= EDITOR_MAX_LINES)
        return;

    editor_cursor_column = 0;
    editor_preferred_column = 0;
}

void editor_cursor_end(void)
{
    if (editor_cursor_row >= EDITOR_MAX_LINES)
        return;

    editor_cursor_column =
        editor_lines[editor_cursor_row].length;

    editor_preferred_column =
        editor_cursor_column;
}

void editor_cursor_word_left(void)
{
    EditorLine *line;

    if (editor_cursor_row >= EDITOR_MAX_LINES)
        return;

    line =
        &editor_lines[editor_cursor_row];

    /*
     * Skip spaces immediately to the left.
     */
    while (editor_cursor_column > 0 &&
           line->text[editor_cursor_column - 1] == ' ')
    {
        editor_cursor_column--;
    }

    /*
     * Move to the beginning of the current word.
     */
    while (editor_cursor_column > 0 &&
           line->text[editor_cursor_column - 1] != ' ')
    {
        editor_cursor_column--;
    }

    editor_preferred_column =
        editor_cursor_column;
}

void editor_cursor_word_right(void)
{
    EditorLine *line;

    if (editor_cursor_row >= EDITOR_MAX_LINES)
        return;

    line =
        &editor_lines[editor_cursor_row];

    /*
     * Skip the current word.
     */
    while (editor_cursor_column < line->length &&
           line->text[editor_cursor_column] != ' ')
    {
        editor_cursor_column++;
    }

    /*
     * Skip spaces before the next word.
     */
    while (editor_cursor_column < line->length &&
           line->text[editor_cursor_column] == ' ')
    {
        editor_cursor_column++;
    }

    editor_preferred_column =
        editor_cursor_column;
}
