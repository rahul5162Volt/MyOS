#include "state.h"
#include "text.h"
#include "lines.h"
#include "selection.h"
#include "vga.h"

#define VGA_SELECTION_ATTRIBUTE 0x70
#define VGA_CURSOR_ATTRIBUTE    0x1F

void editor_render(void)
{
    unsigned int screen_row = 0;
    unsigned int logical_row = 0;

    while (screen_row < VGA_HEIGHT &&
           logical_row < EDITOR_MAX_LINES)
    {
        unsigned int column = 0;
        unsigned int length =
            editor_get_line_length(logical_row);

        while (column < VGA_WIDTH)
        {
            char character = ' ';
            unsigned char attribute;

            if (column < length)
            {
                character =
                    editor_get_char(
                        logical_row,
                        column
                    );
            }

            if (logical_row == editor_cursor_row &&
                column == editor_cursor_column)
            {
                attribute = VGA_CURSOR_ATTRIBUTE;
            }
            else if (editor_selection_contains(
                        logical_row,
                        column))
            {
                attribute = VGA_SELECTION_ATTRIBUTE;
            }
            else
            {
                attribute = VGA_DEFAULT_ATTRIBUTE;
            }

            vga_write_cell(
                screen_row,
                column,
                character,
                attribute
            );

            column++;
        }

        screen_row++;
        logical_row++;
    }

    while (screen_row < VGA_HEIGHT)
    {
        unsigned int column = 0;

        while (column < VGA_WIDTH)
        {
            vga_write_cell(
                screen_row,
                column,
                ' ',
                VGA_DEFAULT_ATTRIBUTE
            );

            column++;
        }

        screen_row++;
    }
}
