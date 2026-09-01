#include "render.h"
#include "vga.h"
#include "window.h"
#include "screen.h"

#define UI_HEADER_ATTRIBUTE 0x1F
#define UI_STATUS_ATTRIBUTE 0x07

void ui_render_header(void)
{
    unsigned int column = 0;

    while (column < VGA_WIDTH)
    {
        vga_write_cell(
            0,
            column,
            ' ',
            UI_HEADER_ATTRIBUTE
        );

        column++;
    }

    vga_write_cell(0, 0, 'M', UI_HEADER_ATTRIBUTE);
    vga_write_cell(0, 1, 'y', UI_HEADER_ATTRIBUTE);
    vga_write_cell(0, 2, 'O', UI_HEADER_ATTRIBUTE);
    vga_write_cell(0, 3, 'S', UI_HEADER_ATTRIBUTE);

    vga_write_cell(
        0,
        VGA_WIDTH - 4,
        'v',
        UI_HEADER_ATTRIBUTE
    );

    vga_write_cell(
        0,
        VGA_WIDTH - 3,
        '0',
        UI_HEADER_ATTRIBUTE
    );

    vga_write_cell(
        0,
        VGA_WIDTH - 2,
        '.',
        UI_HEADER_ATTRIBUTE
    );

    vga_write_cell(
        0,
        VGA_WIDTH - 1,
        '1',
        UI_HEADER_ATTRIBUTE
    );
}

void ui_render_status(void)
{
    unsigned int column = 0;

    while (column < VGA_WIDTH)
    {
        vga_write_cell(
            VGA_HEIGHT - 1,
            column,
            ' ',
            UI_STATUS_ATTRIBUTE
        );

        column++;
    }

    vga_write_cell(
        VGA_HEIGHT - 1,
        0,
        'R',
        UI_STATUS_ATTRIBUTE
    );

    vga_write_cell(
        VGA_HEIGHT - 1,
        1,
        'e',
        UI_STATUS_ATTRIBUTE
    );

    vga_write_cell(
        VGA_HEIGHT - 1,
        2,
        'a',
        UI_STATUS_ATTRIBUTE
    );

    vga_write_cell(
        VGA_HEIGHT - 1,
        3,
        'd',
        UI_STATUS_ATTRIBUTE
    );

    vga_write_cell(
        VGA_HEIGHT - 1,
        4,
        'y',
        UI_STATUS_ATTRIBUTE
    );
}

void ui_renderer_render(void)
{
    const UI_Window* editor_window;

    vga_clear();

    ui_render_header();

    editor_window =
        ui_screen_get_editor_window();

    ui_window_render(
        editor_window
    );

    ui_render_status();
}
