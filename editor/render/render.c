#include "state.h"
#include "editor_text.h"
#include "lines.h"
#include "selection.h"
#include "vga.h"

#define VGA_SELECTION_ATTRIBUTE 0x70
#define VGA_CURSOR_ATTRIBUTE    0x1F

void editor_render(
    unsigned int row,
    unsigned int column,
    unsigned int width,
    unsigned int height
)
{
    unsigned int screen_row = 0;
    unsigned int logical_row = 0;

    while (screen_row < height &&
           logical_row < EDITOR_MAX_LINES)
    {
        unsigned int screen_column = 0;
        unsigned int length =
            editor_get_line_length(logical_row);

        while (screen_column < width)
        {
            char character = ' ';
            unsigned char attribute;

            if (screen_column < length)
            {
                character =
                    editor_get_char(
                        logical_row,
                        screen_column
                    );
            }

            if (logical_row == editor_cursor_row &&
                screen_column == editor_cursor_column)
            {
                attribute =
                    VGA_CURSOR_ATTRIBUTE;
            }
            else if (editor_selection_contains(
                        logical_row,
                        screen_column))
            {
                attribute =
                    VGA_SELECTION_ATTRIBUTE;
            }
            else
            {
                attribute =
                    VGA_DEFAULT_ATTRIBUTE;
            }

            vga_write_cell(
                row + screen_row,
                column + screen_column,
                character,
                attribute
            );

            screen_column++;
        }

        screen_row++;
        logical_row++;
    }

    while (screen_row < height)
    {
        unsigned int screen_column = 0;

        while (screen_column < width)
        {
            vga_write_cell(
                row + screen_row,
                column + screen_column,
                ' ',
                VGA_DEFAULT_ATTRIBUTE
            );

            screen_column++;
        }

        screen_row++;
    }
}
