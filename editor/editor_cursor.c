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
