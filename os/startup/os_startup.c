#include "os_startup.h"

#include "ui_draw.h"
#include "os_main.h"

static void os_startup_logo(void)
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

static void os_startup_wait_for_main(void)
{
    volatile unsigned long delay;

    for (delay = 0; delay < 250000000UL; delay++)
    {
        __asm__ volatile ("nop");
    }
}

void os_startup_run(void)
{
    os_startup_logo();

    os_startup_wait_for_main();

    os_main_run();
}
