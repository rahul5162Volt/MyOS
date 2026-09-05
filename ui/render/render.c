#include "render.h"
#include "ui_draw.h"
#include "layout.h"
#include "window.h"
#include "screen.h"
#include "ui_text.h"
#include "editor.h"

void ui_render_header(void)
{
    const UI_Panel* panel;
    const UI_Text* title;
    const UI_Text* version;

    panel =
        ui_screen_get_header_panel();

    ui_panel_render(panel);

    title =
        ui_screen_get_header_title();

    version =
        ui_screen_get_header_version();

    ui_text_render(title);
    ui_text_render(version);
}

void ui_render_status(void)
{
    const UI_Panel* panel;
    const UI_Text* status;

    panel =
        ui_screen_get_status_panel();

    ui_panel_render(panel);

    status =
        ui_screen_get_status_text();

    ui_text_render(status);
}

void ui_renderer_render(void)
{
    const UI_Window* editor_window;

    unsigned int editor_row;
    unsigned int editor_column;
    unsigned int editor_width;
    unsigned int editor_height;

    ui_draw_clear();

    ui_render_header();

    editor_window =
        ui_screen_get_editor_window();

    ui_window_render(
        editor_window
    );

    editor_row =
        ui_window_content_row(
            editor_window
        );

    editor_column =
        ui_window_content_column(
            editor_window
        );

    editor_width =
        ui_window_content_width(
            editor_window
        );

    editor_height =
        ui_window_content_height(
            editor_window
        );

    editor_render(
        editor_row,
        editor_column,
        editor_width,
        editor_height
    );

    ui_render_status();
}
