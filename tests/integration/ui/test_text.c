#include "test_text.h"

#include "ui_draw.h"

#define TEXT_COLOR \
(ui_color_t){ \
    .foreground = 0x00FFFFFF, \
    .background = 0x00000000 \
}

void ui_test_text(void)
{
    ui_draw_init();
    ui_draw_clear();

    ui_draw_cell(5, 10, 'T', TEXT_COLOR);
    ui_draw_cell(5, 11, 'e', TEXT_COLOR);
    ui_draw_cell(5, 12, 'x', TEXT_COLOR);
    ui_draw_cell(5, 13, 't', TEXT_COLOR);
    ui_draw_cell(5, 14, ' ', TEXT_COLOR);
    ui_draw_cell(5, 15, 'T', TEXT_COLOR);
    ui_draw_cell(5, 16, 'e', TEXT_COLOR);
    ui_draw_cell(5, 17, 's', TEXT_COLOR);
    ui_draw_cell(5, 18, 't', TEXT_COLOR);
}
