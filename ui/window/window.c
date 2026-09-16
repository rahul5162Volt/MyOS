#include "window.h"
#include "ui_draw.h"

void ui_window_init(
    UI_Window* window,
    unsigned int row,
    unsigned int column,
    unsigned int width,
    unsigned int height,
    const char* title,
    ui_color_t border_color,
    ui_color_t title_color
)
{
    window->row = row;
    window->column = column;

    window->width = width;
    window->height = height;

    window->title = title;

    window->border_color = border_color;
    window->title_color = title_color;
}

void ui_window_render(
    const UI_Window* window
)
{
    unsigned int row;
    unsigned int column;
    const char* title;

    if (window->width < 2 ||
        window->height < 2)
    {
        return;
    }

    /*
     * Top border.
     */

    row = window->row;
    column = window->column;

    while (column <
           window->column + window->width)
    {
        ui_draw_cell(
            row,
            column,
            '-',
            window->border_color
        );

        column++;
    }

    /*
     * Bottom border.
     */

    row =
        window->row +
        window->height -
        1;

    column = window->column;

    while (column <
           window->column + window->width)
    {
        ui_draw_cell(
            row,
            column,
            '-',
            window->border_color
        );

        column++;
    }

    /*
     * Left and right borders.
     */

    row = window->row + 1;

    while (row <
           window->row + window->height - 1)
    {
        ui_draw_cell(
            row,
            window->column,
            '|',
            window->border_color
        );

        ui_draw_cell(
            row,
            window->column +
                window->width -
                1,
            '|',
            window->border_color
        );

        row++;
    }

    /*
     * Title.
     */

    title = window->title;

    if (title != 0)
    {
        column = window->column + 2;

        while (*title != '\0' &&
               column <
                   window->column +
                   window->width -
                   2)
        {
            ui_draw_cell(
                window->row,
                column,
                *title,
                window->title_color
            );

            title++;
            column++;
        }
    }
}

unsigned int ui_window_content_row(
    const UI_Window* window
)
{
    return window->row + 1;
}

unsigned int ui_window_content_column(
    const UI_Window* window
)
{
    return window->column + 1;
}

unsigned int ui_window_content_width(
    const UI_Window* window
)
{
    if (window->width < 2)
    {
        return 0;
    }

    return window->width - 2;
}

unsigned int ui_window_content_height(
    const UI_Window* window
)
{
    if (window->height < 2)
    {
        return 0;
    }

    return window->height - 2;
}
