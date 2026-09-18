#include "test_window.h"

#include "ui_draw.h"
#include "window.h"

#define WINDOW_COLOR \
(ui_color_t){ \
    .foreground = 0x00FFFFFF, \
    .background = 0x00000000 \
}

#define WINDOW_TITLE_COLOR \
(ui_color_t){ \
    .foreground = 0x00000000, \
    .background = 0x00FFFFFF \
}

void ui_test_window(void)
{
    UI_Window window;

    ui_draw_init();
    ui_draw_clear();

    ui_window_init(
        &window,
        5,
        10,
        60,
        15,
        "Test Window",
        WINDOW_COLOR,
        WINDOW_TITLE_COLOR
    );

    ui_window_render(&window);
}
