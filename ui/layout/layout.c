#include "layout.h"
#include "ui_draw.h"

void ui_panel_init(
    UI_Panel* panel,
    unsigned int row,
    unsigned int column,
    unsigned int width,
    unsigned int height,
    char character,
    ui_color_t color
)
{
    panel->row = row;
    panel->column = column;
    panel->width = width;
    panel->height = height;

    panel->character = character;
    panel->color = color;

    panel->visible = 1;
}

void ui_panel_render(
    const UI_Panel* panel
)
{
    unsigned int row;
    unsigned int column;

    if (!panel->visible)
    {
        return;
    }

    row = panel->row;

    while (row <
           panel->row + panel->height)
    {
        column = panel->column;

        while (column <
               panel->column + panel->width)
        {
            ui_draw_cell(
                row,
                column,
                panel->character,
                panel->color
            );

            column++;
        }

        row++;
    }
}
