#include "editor.h"

#define EDITOR_MAX_LINES 25
#define EDITOR_MAX_COLUMNS 80

static unsigned int editor_cursor_row = 0;
static unsigned int editor_cursor_column = 0;
static unsigned int editor_preferred_column = 0;

static unsigned char editor_line_lengths[EDITOR_MAX_LINES];
static unsigned char editor_line_hard_break[EDITOR_MAX_LINES];

void editor_init(void)
{
    editor_cursor_row = 0;
    editor_cursor_column = 0;
    editor_preferred_column = 0;

    unsigned int row = 0;

    while (row < EDITOR_MAX_LINES)
    {
        editor_line_lengths[row] = 0;
        editor_line_hard_break[row] = 0;
        row++;
    }
}

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

void editor_set_cursor(unsigned int row, unsigned int column)
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

unsigned int editor_get_line_length(unsigned int row)
{
    if (row >= EDITOR_MAX_LINES)
        return 0;

    return editor_line_lengths[row];
}

int editor_has_hard_break(unsigned int row)
{
    if (row >= EDITOR_MAX_LINES)
        return 0;

    return editor_line_hard_break[row] != 0;
}

void editor_set_line_length(unsigned int row, unsigned int length)
{
    if (row >= EDITOR_MAX_LINES)
        return;

    if (length > EDITOR_MAX_COLUMNS)
        length = EDITOR_MAX_COLUMNS;

    editor_line_lengths[row] = (unsigned char)length;
}

void editor_set_hard_break(unsigned int row, int hard_break)
{
    if (row >= EDITOR_MAX_LINES)
        return;

    editor_line_hard_break[row] = hard_break ? 1 : 0;
}
