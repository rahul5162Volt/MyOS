#include "state.h"
#include "editor_text.h"
#include "lines.h"
#include "selection.h"
#include "ui_draw.h"

#define EDITOR_DEFAULT_COLOR \
    (ui_color_t){ \
        .foreground = 0x00FFFFFF, \
        .background = 0x00000000 \
    }

#define EDITOR_SELECTION_COLOR \
    (ui_color_t){ \
        .foreground = 0x00000000, \
        .background = 0x00FFFFFF \
    }

#define EDITOR_CURSOR_COLOR \
    (ui_color_t){ \
        .foreground = 0x00FFFFFF, \
        .background = 0x0000FF00 \
    }

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
            ui_color_t color;

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
                color = EDITOR_CURSOR_COLOR;
            }
            else if (editor_selection_contains(
                         logical_row,
                         screen_column))
            {
                color = EDITOR_SELECTION_COLOR;
            }
            else
            {
                color = EDITOR_DEFAULT_COLOR;
            }

            ui_draw_cell(
                row + screen_row,
                column + screen_column,
                character,
                color
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
            ui_draw_cell(
                row + screen_row,
                column + screen_column,
                ' ',
                EDITOR_DEFAULT_COLOR
            );

            screen_column++;
        }

        screen_row++;
    }
}
