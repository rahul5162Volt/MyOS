#include "test_buttons.h"

#include "ui_draw.h"

#define BUTTON_COLOR \
(ui_color_t){ \
    .foreground = 0x00000000, \
    .background = 0x00FFFFFF \
}

void ui_test_buttons(void)
{
    ui_draw_init();
    ui_draw_clear();

    ui_draw_fill_rect(
        5,
        10,
        12,
        3,
        ' ',
        BUTTON_COLOR
    );

    ui_draw_cell(6, 14, 'O', BUTTON_COLOR);
    ui_draw_cell(6, 15, 'K', BUTTON_COLOR);
}
