#include "layout.h"
#include "vga.h"

void ui_panel_init(
    UI_Panel* panel,
    unsigned int row,
    unsigned int column,
    unsigned int width,
    unsigned int height,
    unsigned char attribute
)
{
    panel->row = row;
    panel->column = column;

    panel->width = width;
    panel->height = height;

    panel->attribute = attribute;

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
            vga_write_cell(
                row,
                column,
                ' ',
                panel->attribute
            );

            column++;
        }

        row++;
    }
}
