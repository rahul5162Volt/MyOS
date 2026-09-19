#include "os_startup_screen.h"

#include "ui_draw.h"

void os_startup_screen_show(void)
{
    ui_draw_init();
    ui_draw_clear();

    ui_draw_cell(
        10,
        10,
        'M',
        (ui_color_t){
            .foreground = 0x00FFFFFF,
            .background = 0x00000000
        }
    );

    ui_draw_cell(
        10,
        11,
        'y',
        (ui_color_t){
            .foreground = 0x00FFFFFF,
            .background = 0x00000000
        }
    );

    ui_draw_cell(
        10,
        12,
        'O',
        (ui_color_t){
            .foreground = 0x00FFFFFF,
            .background = 0x00000000
        }
    );

    ui_draw_cell(
        10,
        13,
        'S',
        (ui_color_t){
            .foreground = 0x00FFFFFF,
            .background = 0x00000000
        }
    );
}
