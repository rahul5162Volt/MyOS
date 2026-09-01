#include "editor_text.h"
#include "state.h"
#include "edit.h"

char editor_get_char(unsigned int row, unsigned int column)
{
    if (row >= EDITOR_MAX_LINES)
        return ' ';

    if (column >= EDITOR_MAX_COLUMNS)
        return ' ';

    return editor_lines[row].text[column];
}

void editor_set_char(
    unsigned int row,
    unsigned int column,
    char character
)
{
    if (row >= EDITOR_MAX_LINES)
        return;

    if (column >= EDITOR_MAX_COLUMNS)
        return;

    editor_lines[row].text[column] = character;
}

void editor_insert_char(char character)
{
    EditorLine *line;
    unsigned int index;

    if (editor_cursor_row >= EDITOR_MAX_LINES)
        return;

    line =
        &editor_lines[editor_cursor_row];

    if (line->length >= EDITOR_MAX_COLUMNS)
        return;

    /*
     * Shift existing characters one position
     * to the right.
     */
    index = line->length;

    while (index > editor_cursor_column)
    {
        line->text[index] =
            line->text[index - 1];

        index--;
    }

    /*
     * Insert the new character.
     */
    line->text[editor_cursor_column] =
        character;

    line->length++;

    /*
     * Move cursor after inserted character.
     */
    editor_cursor_column++;

    editor_preferred_column =
        editor_cursor_column;
}
