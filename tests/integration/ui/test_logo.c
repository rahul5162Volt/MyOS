#include "test_logo.h"
#include "ui_draw.h"

#define LOGO_COLOR \
(ui_color_t){ \
    .foreground = 0x00FFFFFF, \
    .background = 0x00000000 \
}

void ui_test_logo(void)
{
    ui_draw_clear();

    ui_draw_cell(
        10,
        10,
        'M',
        LOGO_COLOR
    );

    ui_draw_cell(
        10,
        11,
        'y',
        LOGO_COLOR
    );

    ui_draw_cell(
        10,
        12,
        'O',
        LOGO_COLOR
    );

    ui_draw_cell(
        10,
        13,
        'S',
        LOGO_COLOR
    );
}
