#include "test_menu.h"
#include "test_menu_input.h"

#include "ui_draw.h"

#define MENU_COLOR \
(ui_color_t){ \
    .foreground = 0x00FFFFFF, \
    .background = 0x00000000 \
}

void ui_test_menu(void)
{
    ui_draw_init();
    ui_draw_clear();

    ui_draw_cell(5, 10, 'M', MENU_COLOR);
    ui_draw_cell(5, 11, 'E', MENU_COLOR);
    ui_draw_cell(5, 12, 'N', MENU_COLOR);
    ui_draw_cell(5, 13, 'U', MENU_COLOR);

    ui_draw_cell(7, 12, '1', MENU_COLOR);
    ui_draw_cell(7, 14, 'E', MENU_COLOR);
    ui_draw_cell(7, 15, 'x', MENU_COLOR);
    ui_draw_cell(7, 16, 'i', MENU_COLOR);
    ui_draw_cell(7, 17, 't', MENU_COLOR);

    ui_test_menu_input();
}
