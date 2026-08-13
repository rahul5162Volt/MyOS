#include "vga.h"

#define VGA_MEMORY ((volatile unsigned char*)0xB8000)
#define VGA_ATTRIBUTE 0x07
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_CURSOR_INDEX_PORT 0x3D4
#define VGA_CURSOR_DATA_PORT 0x3D5

static unsigned int vga_cursor = 0;
static unsigned char vga_line_lengths[VGA_HEIGHT];
static unsigned char vga_line_hard_break[VGA_HEIGHT];
static unsigned int vga_preferred_column = 0;

static void outb(unsigned short port, unsigned char value)
{
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

static unsigned int vga_row(void) { return vga_cursor / VGA_WIDTH; }
static unsigned int vga_column(void) { return vga_cursor % VGA_WIDTH; }

static void vga_write_cell(unsigned int row, unsigned int column, char character)
{
    unsigned int offset = row * VGA_WIDTH + column;
    VGA_MEMORY[offset * 2] = character;
    VGA_MEMORY[offset * 2 + 1] = VGA_ATTRIBUTE;
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
}

static void vga_copy_row(unsigned int source, unsigned int destination)
{
    unsigned int column = 0;
    while (column < VGA_WIDTH)
    {
        unsigned int source_offset = source * VGA_WIDTH + column;
        unsigned int destination_offset = destination * VGA_WIDTH + column;
        VGA_MEMORY[destination_offset * 2] = VGA_MEMORY[source_offset * 2];
        VGA_MEMORY[destination_offset * 2 + 1] = VGA_MEMORY[source_offset * 2 + 1];
        column++;
    }
    vga_line_lengths[destination] = vga_line_lengths[source];
    vga_line_hard_break[destination] = vga_line_hard_break[source];
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
    vga_cursor = (VGA_HEIGHT - 1) * VGA_WIDTH;
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

static void vga_insert_character(unsigned int row, unsigned int column, char character)
{
    unsigned int current_row = row;
    unsigned int current_column = column;
    char carry = character;

    while (1)
    {
        unsigned int length = vga_line_lengths[current_row];

        if (current_column < length)
        {
            char displaced = VGA_MEMORY[(current_row * VGA_WIDTH + current_column) * 2];
            vga_write_cell(current_row, current_column, carry);
            carry = displaced;
        }
        else
        {
            vga_write_cell(current_row, current_column, carry);
            vga_line_lengths[current_row]++;
            return;
        }

        current_column++;

        if (current_column >= VGA_WIDTH)
        {
            if (current_row == VGA_HEIGHT - 1)
            {
                vga_scroll();
                current_row = VGA_HEIGHT - 1;
                current_column = 0;
            }
            else
            {
                current_row++;
                current_column = 0;
            }
        }
    }
}

void vga_put_char(char character)
{
    unsigned int row;
    unsigned int column;

    if (character == '\n')
    {
        row = vga_row();
        column = vga_column();

        if (row == VGA_HEIGHT - 1)
        {
            vga_scroll();
            row = VGA_HEIGHT - 1;
            column = 0;
        }
        else
        {
            /*
             * Insert a new line without duplicating the current line.
             * Shift only the rows BELOW the current row, starting from
             * the bottom. The old current row must remain untouched so
             * that the text after the cursor can be moved to row + 1.
             */
            unsigned int shift_row = VGA_HEIGHT - 1;
            while (shift_row > row + 1)
            {
                vga_copy_row(shift_row - 1, shift_row);
                shift_row--;
            }
        }

        {
            unsigned int old_length = vga_line_lengths[row];
            unsigned int remainder_length = old_length - column;
            unsigned int move_count = 0;

            /* Move the text after the cursor onto the newly inserted row. */
            while (move_count < remainder_length)
            {
                char character_to_move =
                    VGA_MEMORY[(row * VGA_WIDTH + column + move_count) * 2];
                vga_write_cell(row + 1, move_count, character_to_move);
                move_count++;
            }

            while (move_count < VGA_WIDTH)
            {
                vga_write_cell(row + 1, move_count, ' ');
                move_count++;
            }

            vga_line_lengths[row] = (unsigned char)column;
            vga_line_lengths[row + 1] = (unsigned char)remainder_length;
            vga_line_hard_break[row] = 1;
            vga_line_hard_break[row + 1] = 0;
        }

        vga_cursor = (row + 1) * VGA_WIDTH;
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

    if (column >= VGA_WIDTH)
    {
        column = 0;
        row++;
        if (row >= VGA_HEIGHT)
        {
            vga_scroll();
            row = VGA_HEIGHT - 1;
        }
        vga_cursor = row * VGA_WIDTH;
    }

    vga_insert_character(row, column, character);

    if (vga_line_lengths[row] >= VGA_WIDTH)
    {
        if (row == VGA_HEIGHT - 1)
            vga_scroll();
        else
            vga_cursor = (row + 1) * VGA_WIDTH;
    }
    else
    {
        vga_cursor++;
    }

    vga_preferred_column = vga_column();
    vga_update_cursor();
}

void vga_backspace(void)
{
    unsigned int row = vga_row();
    unsigned int column = vga_column();

    if (row == 0 && column == 0)
        return;

    if (column > 0)
    {
        unsigned int index = column;
        while (index < vga_line_lengths[row])
        {
            char next_character = VGA_MEMORY[(row * VGA_WIDTH + index) * 2];
            vga_write_cell(row, index - 1, next_character);
            index++;
        }

        vga_line_lengths[row]--;
        vga_write_cell(row, vga_line_lengths[row], ' ');
        vga_cursor--;
        vga_preferred_column = vga_column();
        vga_update_cursor();
        return;
    }

    if (vga_line_hard_break[row - 1])
    {
        unsigned int previous_length = vga_line_lengths[row - 1];
        unsigned int current_length = vga_line_lengths[row];
        unsigned int index = 0;

        while (index < current_length && previous_length < VGA_WIDTH)
        {
            char character = VGA_MEMORY[(row * VGA_WIDTH + index) * 2];
            vga_write_cell(row - 1, previous_length, character);
            previous_length++;
            index++;
        }

        vga_line_lengths[row - 1] = (unsigned char)previous_length;

        {
            unsigned int shift_row = row;
            while (shift_row < VGA_HEIGHT - 1)
            {
                vga_copy_row(shift_row + 1, shift_row);
                shift_row++;
            }
            vga_clear_row(VGA_HEIGHT - 1);
        }

        vga_cursor = (row - 1) * VGA_WIDTH + (previous_length - current_length);
        vga_line_hard_break[row - 1] = 1;
        vga_preferred_column = vga_column();
        vga_update_cursor();
        return;
    }

    if (vga_line_lengths[row - 1] >= VGA_WIDTH)
    {
        vga_cursor = (row - 1) * VGA_WIDTH + (VGA_WIDTH - 1);
        vga_line_lengths[row - 1]--;
        vga_write_cell(row - 1, VGA_WIDTH - 1, ' ');
        vga_preferred_column = vga_column();
        vga_update_cursor();
        return;
    }

    vga_cursor = (row - 1) * VGA_WIDTH + vga_line_lengths[row - 1];
    vga_preferred_column = vga_column();
    vga_update_cursor();
}

void vga_cursor_left(void)
{
    unsigned int row = vga_row();
    unsigned int column = vga_column();

    if (column > 0)
        vga_cursor--;
    else if (row > 0)
        vga_cursor = (row - 1) * VGA_WIDTH + vga_line_lengths[row - 1];

    vga_preferred_column = vga_column();
    vga_update_cursor();
}

void vga_cursor_right(void)
{
    unsigned int row = vga_row();
    unsigned int column = vga_column();

    if (column < vga_line_lengths[row])
        vga_cursor++;
    else if (row < VGA_HEIGHT - 1 && vga_line_lengths[row] == VGA_WIDTH)
        vga_cursor = (row + 1) * VGA_WIDTH;

    vga_preferred_column = vga_column();
    vga_update_cursor();
}

void vga_cursor_up(void)
{
    unsigned int row = vga_row();
    if (row == 0)
        return;

    row--;
    if (vga_preferred_column > vga_line_lengths[row])
        vga_cursor = row * VGA_WIDTH + vga_line_lengths[row];
    else
        vga_cursor = row * VGA_WIDTH + vga_preferred_column;

    vga_update_cursor();
}

void vga_cursor_down(void)
{
    unsigned int row = vga_row();
    if (row >= VGA_HEIGHT - 1)
        return;

    if (vga_line_lengths[row + 1] == 0)
        return;

    row++;
    if (vga_preferred_column > vga_line_lengths[row])
        vga_cursor = row * VGA_WIDTH + vga_line_lengths[row];
    else
        vga_cursor = row * VGA_WIDTH + vga_preferred_column;

    vga_update_cursor();
}

void vga_update_cursor(void)
{
    unsigned short position = (unsigned short)vga_cursor;

    outb(VGA_CURSOR_INDEX_PORT, 0x0F);
    outb(VGA_CURSOR_DATA_PORT, (unsigned char)(position & 0xFF));
    outb(VGA_CURSOR_INDEX_PORT, 0x0E);
    outb(VGA_CURSOR_DATA_PORT, (unsigned char)((position >> 8) & 0xFF));
}
