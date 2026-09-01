#include "viewport.h"
#include "window.h"

void ui_viewport_init(
    UI_Viewport* viewport,
    unsigned int row,
    unsigned int column,
    unsigned int width,
    unsigned int height
)
{
    viewport->row = row;
    viewport->column = column;

    viewport->width = width;
    viewport->height = height;
}

void ui_viewport_from_window(
    UI_Viewport* viewport,
    const UI_Window* window
)
{
    ui_viewport_init(
        viewport,
        ui_window_content_row(window),
        ui_window_content_column(window),
        ui_window_content_width(window),
        ui_window_content_height(window)
    );
}

int ui_viewport_contains(
    const UI_Viewport* viewport,
    unsigned int row,
    unsigned int column
)
{
    if (row < viewport->row)
    {
        return 0;
    }

    if (column < viewport->column)
    {
        return 0;
    }

    if (row >=
        viewport->row +
        viewport->height)
    {
        return 0;
    }

    if (column >=
        viewport->column +
        viewport->width)
    {
        return 0;
    }

    return 1;
}
