#include "editor_render.h"
#include "editor_state.h"
#include "editor_text.h"
#include "editor_lines.h"

#define VGA_MEMORY ((volatile unsigned char*)0xB8000)
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ATTRIBUTE 0x07

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
            unsigned int offset =
                (screen_row * VGA_WIDTH + column) * 2;

            char character = ' ';

            if (column < length)
            {
                character =
                    editor_get_char(logical_row, column);
            }

            VGA_MEMORY[offset] = character;

            if (logical_row == editor_cursor_row &&
                column == editor_cursor_column)
            {
                /*
                * Software cursor:
                * black text on white background.
                */
                VGA_MEMORY[offset + 1] = 0x70;
            }
            else
            {
                VGA_MEMORY[offset + 1] = VGA_ATTRIBUTE;
            }

            column++;
        }

        screen_row++;
        logical_row++;
    }

    /*
     * Clear any remaining VGA rows.
     */
    while (screen_row < VGA_HEIGHT)
    {
        unsigned int column = 0;

        while (column < VGA_WIDTH)
        {
            unsigned int offset =
                (screen_row * VGA_WIDTH + column) * 2;

            VGA_MEMORY[offset] = ' ';
            VGA_MEMORY[offset + 1] = VGA_ATTRIBUTE;

            column++;
        }

        screen_row++;
    }
}
