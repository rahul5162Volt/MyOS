#include "editor_lines.h"
#include "editor_state.h"

unsigned int editor_get_line_length(unsigned int row)
{
    if (row >= EDITOR_MAX_LINES)
        return 0;

    return editor_lines[row].length;
}

unsigned int editor_has_hard_break(unsigned int row)
{
    if (row >= EDITOR_MAX_LINES)
        return 0;

    return editor_lines[row].hard_break;
}

void editor_set_line_length(
    unsigned int row,
    unsigned int length
)
{
    if (row >= EDITOR_MAX_LINES)
        return;

    if (length > EDITOR_MAX_COLUMNS)
        length = EDITOR_MAX_COLUMNS;

    editor_lines[row].length = length;
}

void editor_set_hard_break(
    unsigned int row,
    unsigned int hard_break
)
{
    if (row >= EDITOR_MAX_LINES)
        return;

    if (hard_break)
        editor_lines[row].hard_break = 1;
    else
        editor_lines[row].hard_break = 0;
}
