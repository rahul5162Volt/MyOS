#include "editor_clipboard.h"
#include "editor_selection.h"
#include "editor_state.h"
#include "editor_text.h"
#include "editor_lines.h"
#include "editor_edit.h"

#define EDITOR_CLIPBOARD_MAX_LINES   EDITOR_MAX_LINES
#define EDITOR_CLIPBOARD_MAX_COLUMNS EDITOR_MAX_COLUMNS

typedef struct
{
    char text[EDITOR_CLIPBOARD_MAX_COLUMNS];
    unsigned int length;
    unsigned char hard_break;
} EditorClipboardLine;

static EditorClipboardLine
    editor_clipboard_lines[EDITOR_CLIPBOARD_MAX_LINES];

static unsigned int
    editor_clipboard_line_count = 0;

static unsigned int
    editor_clipboard_active = 0;

void editor_clipboard_clear(void)
{
    unsigned int row;
    unsigned int column;

    editor_clipboard_line_count = 0;
    editor_clipboard_active = 0;

    row = 0;

    while (row < EDITOR_CLIPBOARD_MAX_LINES)
    {
        editor_clipboard_lines[row].length = 0;
        editor_clipboard_lines[row].hard_break = 0;

        column = 0;

        while (column < EDITOR_CLIPBOARD_MAX_COLUMNS)
        {
            editor_clipboard_lines[row].text[column] = ' ';
            column++;
        }

        row++;
    }
}

unsigned int editor_clipboard_has_data(void)
{
    return editor_clipboard_active;
}

void editor_clipboard_copy_selection(void)
{
    unsigned int start_row;
    unsigned int start_column;
    unsigned int end_row;
    unsigned int end_column;

    unsigned int row;
    unsigned int column;

    if (!editor_selection_is_active())
        return;

    if (!editor_selection_has_anchor())
        return;

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
        return;
    }

    editor_clipboard_clear();

    /*
     * Single-line selection.
     */
    if (start_row == end_row)
    {
        EditorLine *line =
            &editor_lines[start_row];

        editor_clipboard_line_count = 1;

        column = start_column;

        while (column < end_column)
        {
            editor_clipboard_lines[0].text[
                column - start_column
            ] =
                line->text[column];

            column++;
        }

        editor_clipboard_lines[0].length =
            end_column - start_column;

        editor_clipboard_lines[0].hard_break = 0;

        editor_clipboard_active = 1;

        return;
    }

    /*
     * First selected line.
     */
    {
        EditorLine *line =
            &editor_lines[start_row];

        unsigned int clipboard_column = 0;

        column = start_column;

        while (column < line->length)
        {
            editor_clipboard_lines[0].text[
                clipboard_column
            ] =
                line->text[column];

            clipboard_column++;
            column++;
        }

        editor_clipboard_lines[0].length =
            clipboard_column;

        editor_clipboard_lines[0].hard_break = 1;
    }

    /*
     * Lines completely inside the selection.
     */
    row = start_row + 1;

    while (row < end_row &&
           row - start_row < EDITOR_CLIPBOARD_MAX_LINES)
    {
        EditorLine *line =
            &editor_lines[row];

        unsigned int clipboard_row =
            row - start_row;

        column = 0;

        while (column < line->length)
        {
            editor_clipboard_lines[
                clipboard_row
            ].text[column] =
                line->text[column];

            column++;
        }

        editor_clipboard_lines[
            clipboard_row
        ].length =
            line->length;

        editor_clipboard_lines[
            clipboard_row
        ].hard_break = 1;

        row++;
    }

    /*
     * Last selected line.
     */
    if (end_row - start_row < EDITOR_CLIPBOARD_MAX_LINES)
    {
        EditorLine *line =
            &editor_lines[end_row];

        unsigned int clipboard_row =
            end_row - start_row;

        unsigned int clipboard_column = 0;

        column = 0;

        while (column < end_column)
        {
            editor_clipboard_lines[
                clipboard_row
            ].text[clipboard_column] =
                line->text[column];

            clipboard_column++;
            column++;
        }

        editor_clipboard_lines[
            clipboard_row
        ].length =
            clipboard_column;

        editor_clipboard_lines[
            clipboard_row
        ].hard_break = 0;

        editor_clipboard_line_count =
            clipboard_row + 1;
    }

    editor_clipboard_active = 1;
}

void editor_clipboard_paste(void)
{
    unsigned int row;
    unsigned int column;
    unsigned int required_lines;
    unsigned int required_columns;
    EditorLine *current_line;

    if (!editor_clipboard_active)
        return;

    if (editor_clipboard_line_count == 0)
        return;

    if (editor_cursor_row >= EDITOR_MAX_LINES)
        return;

    /*
     * Make sure the paste will fit before modifying
     * the document.
     */
    required_lines =
        editor_clipboard_line_count - 1;

    if (editor_cursor_row + required_lines >=
        EDITOR_MAX_LINES)
    {
        return;
    }

    /*
     * The first clipboard line is inserted into
     * the current line.
     *
     * The existing text after the cursor will be
     * preserved by editor_insert_newline().
     */
    current_line =
        &editor_lines[editor_cursor_row];

    required_columns =
        current_line->length -
        editor_cursor_column +
        editor_clipboard_lines[0].length;

    if (required_columns > EDITOR_MAX_COLUMNS)
    {
        return;
    }

    /*
     * Insert the first clipboard line.
     */
    column = 0;

    while (column <
           editor_clipboard_lines[0].length)
    {
        editor_insert_char(
            editor_clipboard_lines[0].text[column]
        );

        column++;
    }

    /*
     * Each additional clipboard line becomes a
     * new logical line.
     */
    row = 1;

    while (row < editor_clipboard_line_count)
    {
        editor_insert_newline();

        column = 0;

        while (column <
               editor_clipboard_lines[row].length)
        {
            editor_insert_char(
                editor_clipboard_lines[row].text[column]
            );

            column++;
        }

        row++;
    }
}
