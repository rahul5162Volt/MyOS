#include "screen.h"
#include "layout.h"
#include "window.h"
#include "ui_text.h"
#include "ui_draw.h"

#define UI_HEADER_COLOR \
    (ui_color_t){ \
        .foreground = 0x00FFFFFF, \
        .background = 0x000000FF \
    }

#define UI_STATUS_COLOR \
    (ui_color_t){ \
        .foreground = 0x00FFFFFF, \
        .background = 0x00000000 \
    }

#define UI_WINDOW_BORDER_COLOR \
    (ui_color_t){ \
        .foreground = 0x00FFFFFF, \
        .background = 0x00000000 \
    }

#define UI_WINDOW_TITLE_COLOR \
    (ui_color_t){ \
        .foreground = 0x00000000, \
        .background = 0x00FFFFFF \
    }

static UI_Panel header_panel;
static UI_Window editor_window;
static UI_Panel status_panel;

static UI_Text header_title;
static UI_Text header_version;
static UI_Text status_text;

void ui_screen_init(void)
{
    ui_draw_init();

    ui_panel_init(
        &header_panel,
        0,
        0,
        ui_draw_get_width(),
        1,
        ' ',
        UI_HEADER_COLOR
    );

    ui_window_init(
        &editor_window,
        3,
        2,
        ui_draw_get_width() - 4,
        ui_draw_get_height() - 6,
        "Editor",
        UI_WINDOW_BORDER_COLOR,
        UI_WINDOW_TITLE_COLOR
    );

    ui_panel_init(
        &status_panel,
        ui_draw_get_height() - 1,
        0,
        ui_draw_get_width(),
        1,
        ' ',
        UI_STATUS_COLOR
    );

    ui_text_init(
        &header_title,
        0,
        0,
        "MyOS",
        UI_HEADER_COLOR
    );

    ui_text_init(
        &header_version,
        0,
        ui_draw_get_width() - 4,
        "v0.1",
        UI_HEADER_COLOR
    );

    ui_text_init(
        &status_text,
        ui_draw_get_height() - 1,
        0,
        "Ready",
        UI_STATUS_COLOR
    );
}

const UI_Panel* ui_screen_get_header_panel(void)
{
    return &header_panel;
}

const UI_Window* ui_screen_get_editor_window(void)
{
    return &editor_window;
}

const UI_Panel* ui_screen_get_status_panel(void)
{
    return &status_panel;
}

const UI_Text* ui_screen_get_header_title(void)
{
    return &header_title;
}

const UI_Text* ui_screen_get_header_version(void)
{
    return &header_version;
}

const UI_Text* ui_screen_get_status_text(void)
{
    return &status_text;
}
