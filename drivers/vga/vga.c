#include "vga.h"
#include "../../editor/editor.h"

#pragma GCC optimize ("Os")

#define VGA_MEMORY ((volatile unsigned char*)0xB8000)
#define VGA_ATTRIBUTE 0x07
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_CURSOR_INDEX_PORT 0x3D4
#define VGA_CURSOR_DATA_PORT 0x3D5

static unsigned int vga_cursor = 0;

static void vga_disable_cursor(void);

static unsigned char vga_line_lengths[VGA_HEIGHT];
static unsigned char vga_line_hard_break[VGA_HEIGHT];

static unsigned int vga_preferred_column = 0;

static void outb(unsigned short port, unsigned char value)
{
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

static unsigned int vga_row(void)
{
    return vga_cursor / VGA_WIDTH;
}

static unsigned int vga_column(void)
{
    return vga_cursor % VGA_WIDTH;
}

static void vga_sync_line_state(unsigned int row)
{
    editor_set_line_length(
        row,
        vga_line_lengths[row]
    );

    editor_set_hard_break(
        row,
        vga_line_hard_break[row]
    );
}

static void vga_write_cell(
    unsigned int row,
    unsigned int column,
    char character)
{
    unsigned int offset = row * VGA_WIDTH + column;

    VGA_MEMORY[offset * 2] = character;
    VGA_MEMORY[offset * 2 + 1] = VGA_ATTRIBUTE;
}

static char vga_read_cell(
    unsigned int row,
    unsigned int column)
{
    unsigned int offset = row * VGA_WIDTH + column;

    return VGA_MEMORY[offset * 2];
}

static void vga_clear_row(unsigned int row)
{
    unsigned int column = 0;

    while (column < VGA_WIDTH)
    {
        vga_write_cell(row, column, ' ');
        column++;
    }

    vga_line_lengths[row] = 0;
    vga_line_hard_break[row] = 0;

    vga_sync_line_state(row);
}

static void vga_copy_row(
    unsigned int source,
    unsigned int destination)
{
    unsigned int column = 0;

    while (column < VGA_WIDTH)
    {
        unsigned int source_offset =
            source * VGA_WIDTH + column;

        unsigned int destination_offset =
            destination * VGA_WIDTH + column;

        VGA_MEMORY[destination_offset * 2] =
            VGA_MEMORY[source_offset * 2];

        VGA_MEMORY[destination_offset * 2 + 1] =
            VGA_MEMORY[source_offset * 2 + 1];

        column++;
    }

    /*
     * Copy editor metadata together with the
     * physical VGA row.
     */
    vga_line_lengths[destination] =
        vga_line_lengths[source];

    vga_line_hard_break[destination] =
        vga_line_hard_break[source];

    vga_sync_line_state(destination);
}

static void vga_scroll(void)
{
    unsigned int row = 1;

    while (row < VGA_HEIGHT)
    {
        vga_copy_row(row, row - 1);
        row++;
    }

    vga_clear_row(VGA_HEIGHT - 1);

    vga_cursor =
        (VGA_HEIGHT - 1) * VGA_WIDTH;

    vga_preferred_column = 0;
}

void vga_clear(void)
{
    unsigned int row = 0;

    while (row < VGA_HEIGHT)
    {
        vga_clear_row(row);
        row++;
    }

    vga_cursor = 0;
    vga_preferred_column = 0;

    vga_disable_cursor();

    vga_update_cursor();
}

void vga_print(const char* text)
{
    while (*text != '\0')
    {
        vga_put_char(*text);
        text++;
    }
}

/*
 * Insert one character at the current position.
 *
 * Text after the insertion point is shifted right.
 * If a row becomes full, the displaced character
 * continues onto the next row.
 */
static void vga_insert_character(
    unsigned int row,
    unsigned int column,
    char character)
{
    char carry = character;

    while (1)
    {
        unsigned int length =
            editor_get_line_length(row);

        if (column < length)
        {
            char displaced =
                vga_read_cell(row, column);

            vga_write_cell(
                row,
                column,
                carry);

            carry = displaced;
        }
        else
        {
            vga_write_cell(
                row,
                column,
                carry);

            if (editor_get_line_length(row) < VGA_WIDTH)
            {
                editor_set_line_length(
                    row,
                    editor_get_line_length(row) + 1
                );

                vga_line_lengths[row] =
                    (unsigned char)editor_get_line_length(row);
            }

            return;
        }

        column++;

        if (column >= VGA_WIDTH)
        {
            if (row == VGA_HEIGHT - 1)
            {
                /*
                 * The character must continue on a new
                 * screen row. Scroll first so row 24
                 * remains valid.
                 */
                vga_scroll();

                row = VGA_HEIGHT - 1;
                column = 0;
            }
            else
            {
                row++;
                column = 0;
            }
        }
    }
}

static void vga_insert_empty_row(unsigned int row)
{
    unsigned int shift_row;

    /*
     * When there is no space at the bottom, scrolling
     * creates the required row while keeping the cursor
     * inside the VGA screen.
     */
    if (row >= VGA_HEIGHT - 1)
    {
        vga_scroll();
        return;
    }

    shift_row = VGA_HEIGHT - 1;

    while (shift_row > row)
    {
        vga_copy_row(
            shift_row - 1,
            shift_row);

        shift_row--;
    }

    vga_clear_row(row + 1);
}

void vga_put_char(char character)
{
    unsigned int row;
    unsigned int column;

    if (character == '\n')
    {
        unsigned int old_length;
        unsigned int remainder_length;
        unsigned int move_count;

        row = vga_row();
        column = vga_column();

        /*
         * Never allow an invalid row.
         */
        if (row >= VGA_HEIGHT)
        {
            vga_cursor =
                (VGA_HEIGHT - 1) * VGA_WIDTH;

            row = VGA_HEIGHT - 1;
            column = 0;
        }

        old_length =
            editor_get_line_length(row);

        /*
         * The cursor may legally be at the end of a line.
         */
        if (column > old_length)
            column = old_length;

        remainder_length =
            old_length - column;

        if (row == VGA_HEIGHT - 1)
        {
            vga_scroll();
            row--;
        }
        else
            vga_insert_empty_row(row);

        /*
         * Move only the text that was AFTER the cursor
         * onto the newly inserted row.
         */
        move_count = 0;

        while (move_count < remainder_length)
        {
            char character_to_move =
                vga_read_cell(
                    row,
                    column + move_count);

            vga_write_cell(
                row + 1,
                move_count,
                character_to_move);

            move_count++;
        }

        /*
         * Clear the unused portion of the new row.
         */
        while (move_count < VGA_WIDTH)
        {
            vga_write_cell(
                row + 1,
                move_count,
                ' ');

            move_count++;
        }

        move_count = column;

        while (move_count < VGA_WIDTH)
        {
            vga_write_cell(
                row,
                move_count,
                ' ');

            move_count++;
        }

        editor_set_line_length(row, column);
        editor_set_line_length(row + 1, remainder_length);

        editor_set_hard_break(row, 1);
        editor_set_hard_break(row + 1, 0);

        vga_line_lengths[row] =
            (unsigned char)editor_get_line_length(row);

        vga_line_lengths[row + 1] =
            (unsigned char)editor_get_line_length(row + 1);

        vga_sync_line_state(row);
        vga_sync_line_state(row + 1);

        /*
         * Cursor moves to the beginning of the new line.
         */
        vga_cursor =
            (row + 1) * VGA_WIDTH;

        vga_preferred_column = 0;

        vga_update_cursor();
        return;
    }

    if (character == '\r')
    {
        vga_cursor -= vga_column();

        vga_preferred_column = 0;

        vga_update_cursor();
        return;
    }

    row = vga_row();
    column = vga_column();

    /*
     * Safety check.
     */
    if (row >= VGA_HEIGHT)
    {
        vga_cursor =
            (VGA_HEIGHT - 1) * VGA_WIDTH;

        row = VGA_HEIGHT - 1;
        column = 0;
    }

    if (column >= VGA_WIDTH)
    {
        column = 0;
        row++;

        if (row >= VGA_HEIGHT)
        {
            vga_scroll();
            row = VGA_HEIGHT - 1;
        }

        vga_cursor =
            row * VGA_WIDTH;
    }

    vga_insert_character(
        row,
        column,
        character);

    /*
     * If the line became full, move to the next row.
     */
    if (editor_get_line_length(row) >= VGA_WIDTH)
    {
        if (row == VGA_HEIGHT - 1)
        {
            vga_scroll();
        }
        else
        {
            vga_cursor =
                (row + 1) * VGA_WIDTH;
        }
    }
    else
    {
        vga_cursor++;
    }

    vga_preferred_column =
        vga_column();

    vga_update_cursor();
}

void vga_backspace(void)
{
    unsigned int row = vga_row();
    unsigned int column = vga_column();

    if (row >= VGA_HEIGHT)
    {
        vga_cursor =
            (VGA_HEIGHT - 1) * VGA_WIDTH;

        row = VGA_HEIGHT - 1;
        column = 0;
    }

    if (row == 0 && column == 0)
        return;

    /*
     * Normal deletion inside a line.
     */
    if (column > 0)
    {
        unsigned int index = column;

        while (index < editor_get_line_length(row))
        {
            char next_character =
                vga_read_cell(row, index);

            vga_write_cell(
                row,
                index - 1,
                next_character);

            index++;
        }

        /*
         * Update VGA state first.
         */
        vga_line_lengths[row]--;

        /*
         * Synchronize VGA state -> editor state.
         */
        vga_sync_line_state(row);

        /*
         * Clear the now-unused final cell.
         */
        vga_write_cell(
            row,
            editor_get_line_length(row),
            ' ');

        vga_cursor--;

        vga_preferred_column =
            vga_column();

        vga_update_cursor();
        return;
    }

    /*
     * Cursor is at column zero.
     *
     * If the previous physical row was created by
     * Enter, remove that hard break and merge the
     * current line back into it.
     */
    if (row > 0 && editor_has_hard_break(row - 1))
    {
        unsigned int previous_length =
            editor_get_line_length(row - 1);

        unsigned int current_length =
            editor_get_line_length(row);

        unsigned int index = 0;

        /*
         * Append the current line to the previous line.
         */
        while (index < current_length &&
               previous_length < VGA_WIDTH)
        {
            char character =
                vga_read_cell(row, index);

            vga_write_cell(
                row - 1,
                previous_length,
                character);

            previous_length++;
            index++;
        }

        /*
         * IMPORTANT:
         *
         * Update the VGA-side state first.
         * vga_sync_line_state() copies this state
         * into the editor layer.
         */
        vga_line_lengths[row - 1] =
            (unsigned char)previous_length;

        /*
         * The hard-break state of the current line
         * becomes the hard-break state of the merged
         * line.
         */
        vga_line_hard_break[row - 1] =
            (unsigned char)editor_has_hard_break(row);

        /*
         * Synchronize the merged line.
         */
        vga_sync_line_state(row - 1);

        /*
         * Remove the current physical row by shifting
         * everything below it upward.
         */
        {
            unsigned int shift_row = row;

            while (shift_row < VGA_HEIGHT - 1)
            {
                vga_copy_row(
                    shift_row + 1,
                    shift_row);

                shift_row++;
            }

            vga_clear_row(VGA_HEIGHT - 1);
        }

        /*
         * Cursor returns to the end of the merged line.
         */
        vga_cursor =
            (row - 1) * VGA_WIDTH +
            previous_length;

        vga_preferred_column =
            vga_column();

        vga_update_cursor();
        return;
    }

    /*
     * Wrapped-line boundary.
     *
     * The previous physical row is full, so this is
     * a soft wrap rather than an Enter-created line.
     *
     * Move to the final character of that row and
     * delete it.
     */
    if (row > 0 &&
        editor_get_line_length(row - 1) >= VGA_WIDTH)
    {
        vga_cursor =
            (row - 1) * VGA_WIDTH +
            (VGA_WIDTH - 1);

        /*
         * Update VGA-side state first.
         */
        vga_line_lengths[row - 1]--;

        vga_sync_line_state(row - 1);

        vga_write_cell(
            row - 1,
            VGA_WIDTH - 1,
            ' ');

        vga_preferred_column =
            vga_column();

        vga_update_cursor();
        return;
    }

    /*
     * Empty/new physical line.
     *
     * There is no hard break and the previous line is
     * not a wrapped full line. Simply move the cursor
     * to the end of the previous line.
     */
    vga_cursor =
        (row - 1) * VGA_WIDTH +
        editor_get_line_length(row - 1);

    vga_preferred_column =
        vga_column();

    vga_update_cursor();
}

void vga_update_cursor(void)
{
}

static void vga_disable_cursor(void)
{
    outb(VGA_CURSOR_INDEX_PORT, 0x0A);
    outb(VGA_CURSOR_DATA_PORT, 0x20);

    outb(VGA_CURSOR_INDEX_PORT, 0x0B);
    outb(VGA_CURSOR_DATA_PORT, 0x00);
}

void vga_render_editor(void)
{
    unsigned int row = 0;

    while (row < VGA_HEIGHT)
    {
        unsigned int column = 0;
        unsigned int length =
            editor_get_line_length(row);

        while (column < VGA_WIDTH)
        {
            char character = ' ';

            if (column < length)
                character = editor_get_char(row, column);

            vga_write_cell(
                row,
                column,
                character
            );

            column++;
        }

        row++;
    }

    vga_cursor =
        editor_get_cursor_row() * VGA_WIDTH +
        editor_get_cursor_column();

    vga_preferred_column =
        editor_get_preferred_column();

    vga_update_cursor();
}
