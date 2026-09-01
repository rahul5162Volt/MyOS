#include "screen.h"
#include "window.h"
#include "vga.h"

static UI_Window editor_window;

void ui_screen_init(void)
{
    ui_window_init(
        &editor_window,
        3,
        2,
        VGA_WIDTH - 4,
        VGA_HEIGHT - 6,
        "Editor"
    );
}

const UI_Window* ui_screen_get_editor_window(void)
{
    return &editor_window;
}
