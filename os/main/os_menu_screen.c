#include "os_menu_screen.h"

#include "ui_draw.h"

#define OS_MENU_NORMAL_COLOR \
(ui_color_t){ \
    .foreground = 0x00FFFFFF, \
    .background = 0x00000000 \
}

#define OS_MENU_SELECTED_COLOR \
(ui_color_t){ \
    .foreground = 0x00000000, \
    .background = 0x00FFFFFF \
}

#define OS_MENU_TITLE_ROW       5
#define OS_MENU_TITLE_COLUMN    10

#define OS_MENU_EDITOR_ROW      7
#define OS_MENU_CALCULATOR_ROW  8

#define OS_MENU_KEY_COLUMN      10
#define OS_MENU_LABEL_COLUMN    12

void os_menu_screen_show(void)
{
    ui_draw_clear();

    ui_draw_string(
        OS_MENU_TITLE_ROW,
        OS_MENU_TITLE_COLUMN,
        "MAIN",
        OS_MENU_NORMAL_COLOR
    );

    ui_draw_cell(
        OS_MENU_EDITOR_ROW,
        OS_MENU_KEY_COLUMN,
        '1',
        OS_MENU_SELECTED_COLOR
    );

    ui_draw_string(
        OS_MENU_EDITOR_ROW,
        OS_MENU_LABEL_COLUMN,
        "Editor",
        OS_MENU_NORMAL_COLOR
    );

    ui_draw_cell(
        OS_MENU_CALCULATOR_ROW,
        OS_MENU_KEY_COLUMN,
        '2',
        OS_MENU_SELECTED_COLOR
    );

    ui_draw_string(
        OS_MENU_CALCULATOR_ROW,
        OS_MENU_LABEL_COLUMN,
        "Calculator",
        OS_MENU_NORMAL_COLOR
    );
}
