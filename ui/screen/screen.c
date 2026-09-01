#include "screen.h"
#include "layout.h"
#include "window.h"
#include "ui_text.h"
#include "vga.h"

#define UI_HEADER_ATTRIBUTE 0x1F
#define UI_STATUS_ATTRIBUTE 0x07

static UI_Panel header_panel;
static UI_Window editor_window;
static UI_Panel status_panel;

static UI_Text header_title;
static UI_Text header_version;
static UI_Text status_text;

void ui_screen_init(void)
{
    ui_panel_init(
        &header_panel,
        0,
        0,
        VGA_WIDTH,
        1,
        UI_HEADER_ATTRIBUTE
    );

    ui_window_init(
        &editor_window,
        3,
        2,
        VGA_WIDTH - 4,
        VGA_HEIGHT - 6,
        "Editor"
    );

    ui_panel_init(
        &status_panel,
        VGA_HEIGHT - 1,
        0,
        VGA_WIDTH,
        1,
        UI_STATUS_ATTRIBUTE
    );

    ui_text_init(
        &header_title,
        0,
        0,
        "MyOS",
        UI_HEADER_ATTRIBUTE
    );

    ui_text_init(
        &header_version,
        0,
        VGA_WIDTH - 4,
        "v0.1",
        UI_HEADER_ATTRIBUTE
    );

    ui_text_init(
        &status_text,
        VGA_HEIGHT - 1,
        0,
        "Ready",
        UI_STATUS_ATTRIBUTE
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
