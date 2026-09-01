#include "selection.h"
#include "state.h"
#include "editor_text.h"
#include "lines.h"

void editor_selection_start(void)
{
    editor_selection_anchor_row =
        editor_cursor_row;

    editor_selection_anchor_column =
        editor_cursor_column;

    editor_selection_anchor_active = 1;
    editor_selection_active = 1;
}

void editor_selection_update(void)
{
    if (!editor_selection_active)
        return;
}

void editor_selection_clear(void)
{
    editor_selection_active = 0;
    editor_selection_anchor_active = 0;
}

unsigned int editor_selection_is_active(void)
{
    return editor_selection_active;
}

int editor_selection_contains(
    unsigned int row,
    unsigned int column
)
{
    unsigned int start_row;
    unsigned int start_column;
    unsigned int end_row;
    unsigned int end_column;

    if (!editor_selection_anchor_active)
        return 0;

    /*
     * The anchor is fixed.
     * The cursor is the moving endpoint.
     */
    start_row = editor_selection_anchor_row;
    start_column = editor_selection_anchor_column;

    end_row = editor_cursor_row;
    end_column = editor_cursor_column;

    /*
     * Normalize selection direction.
     */
    if (start_row > end_row ||
        (start_row == end_row &&
         start_column > end_column))
    {
        unsigned int temp;

        temp = start_row;
        start_row = end_row;
        end_row = temp;

        temp = start_column;
        start_column = end_column;
        end_column = temp;
    }

    /*
     * Empty selection.
     */
    if (start_row == end_row &&
        start_column == end_column)
    {
        return 0;
    }

    /*
     * Outside selection.
     */
    if (row < start_row ||
        row > end_row)
    {
        return 0;
    }

    /*
     * Single-line selection.
     */
    if (start_row == end_row)
    {
        return row == start_row &&
               column >= start_column &&
               column < end_column;
    }

    /*
     * First selected line.
     */
    if (row == start_row)
    {
        return column >= start_column;
    }

    /*
     * Last selected line.
     */
    if (row == end_row)
    {
        return column < end_column;
    }

    /*
     * Lines completely inside selection.
     */
    return 1;
}

void editor_selection_to_home(void)
{
    editor_cursor_column = 0;
    editor_preferred_column = 0;

    editor_selection_update();
}

void editor_selection_to_end(void)
{
    unsigned int length;

    length =
        editor_get_line_length(editor_cursor_row);

    editor_cursor_column = length;
    editor_preferred_column = length;

    editor_selection_update();
}

void editor_selection_delete(void)
{
    unsigned int start_row;
    unsigned int start_column;
    unsigned int end_row;
    unsigned int end_column;

    unsigned int row;
    unsigned int column;
    unsigned int index;

    if (!editor_selection_anchor_active)
        return;

    /*
     * The anchor is fixed.
     * The cursor is the moving endpoint.
     */
    start_row = editor_selection_anchor_row;
    start_column = editor_selection_anchor_column;

    end_row = editor_cursor_row;
    end_column = editor_cursor_column;

    /*
     * Normalize selection direction.
     */
    if (start_row > end_row ||
        (start_row == end_row &&
         start_column > end_column))
    {
        unsigned int temp;

        temp = start_row;
        start_row = end_row;
        end_row = temp;

        temp = start_column;
        start_column = end_column;
        end_column = temp;
    }

    /*
     * Empty selection.
     */
    if (start_row == end_row &&
        start_column == end_column)
    {
        editor_selection_clear();
        return;
    }

    /*
     * Same-line selection.
     */
    if (start_row == end_row)
    {
        EditorLine *line =
            &editor_lines[start_row];

        index = start_column;

        while (index +
               (end_column - start_column) <
               line->length)
        {
            line->text[index] =
                line->text[
                    index +
                    (end_column - start_column)
                ];

            index++;
        }

        line->length -=
            end_column - start_column;

        while (index <
               line->length +
               (end_column - start_column))
        {
            line->text[index] = ' ';
            index++;
        }

        editor_cursor_row =
            start_row;

        editor_cursor_column =
            start_column;

        editor_preferred_column =
            start_column;

        editor_selection_clear();

        return;
    }

    /*
     * Multi-line selection.
     */
    {
        EditorLine *first_line =
            &editor_lines[start_row];

        EditorLine *last_line =
            &editor_lines[end_row];

        unsigned int first_length =
            start_column;

        unsigned int suffix_length =
            last_line->length -
            end_column;

        /*
         * Make sure the resulting line fits.
         */
        if (first_length +
            suffix_length >
            EDITOR_MAX_COLUMNS)
        {
            return;
        }

        /*
         * Copy the suffix of the last line
         * onto the first line.
         */
        column = 0;

        while (column < suffix_length)
        {
            first_line->text[
                first_length + column
            ] =
                last_line->text[
                    end_column + column
                ];

            column++;
        }

        first_line->length =
            first_length +
            suffix_length;

        /*
         * Preserve the hard break of the
         * last line.
         */
        first_line->hard_break =
            last_line->hard_break;

        /*
         * Remove the logical lines consumed
         * by the selection.
         */
        row = start_row + 1;

        while (row +
               (end_row - start_row) <
               EDITOR_MAX_LINES)
        {
            editor_lines[row] =
                editor_lines[
                    row +
                    (end_row - start_row)
                ];

            row++;
        }

        /*
         * Clear unused lines.
         */
        while (row < EDITOR_MAX_LINES)
        {
            editor_lines[row].length = 0;
            editor_lines[row].hard_break = 0;

            column = 0;

            while (column < EDITOR_MAX_COLUMNS)
            {
                editor_lines[row].text[column] = ' ';
                column++;
            }

            row++;
        }

        /*
         * Cursor returns to the beginning
         * of the deleted selection.
         */
        editor_cursor_row =
            start_row;

        editor_cursor_column =
            start_column;

        editor_preferred_column =
            start_column;

        editor_selection_clear();
    }
}

void editor_selection_all(void)
{
    unsigned int last_row;
    unsigned int last_column;

    last_row = 0;

    /*
     * Find the last logical line containing text
     * or the last line that is explicitly present.
     */
    while (last_row < EDITOR_MAX_LINES - 1)
    {
        if (editor_get_line_length(last_row + 1) == 0 &&
            !editor_has_hard_break(last_row))
        {
            break;
        }

        last_row++;
    }

    last_column =
        editor_get_line_length(last_row);

    editor_selection_anchor_row = 0;
    editor_selection_anchor_column = 0;

    editor_cursor_row = last_row;
    editor_cursor_column = last_column;
    editor_preferred_column = last_column;

    editor_selection_anchor_active = 1;
    editor_selection_active = 1;
}

void editor_selection_to_document_start(void)
{
    if (!editor_selection_active)
        return;

    editor_cursor_row = 0;
    editor_cursor_column = 0;
    editor_preferred_column = 0;
}

void editor_selection_to_document_end(void)
{
    unsigned int last_row = 0;
    unsigned int last_column;

    if (!editor_selection_active)
        return;

    while (last_row < EDITOR_MAX_LINES - 1)
    {
        if (editor_get_line_length(last_row + 1) == 0 &&
            !editor_has_hard_break(last_row))
        {
            break;
        }

        last_row++;
    }

    last_column =
        editor_get_line_length(last_row);

    editor_cursor_row = last_row;
    editor_cursor_column = last_column;
    editor_preferred_column = last_column;
}

unsigned int editor_selection_has_anchor(void)
{
    return editor_selection_anchor_active;
}