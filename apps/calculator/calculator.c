#include "calculator.h"
#include "application_runtime.h"

#include "ui_draw.h"
#include "keyboard/keyboard.h"

#define CALCULATOR_NORMAL_COLOR \
(ui_color_t){ \
    .foreground = 0x00FFFFFF, \
    .background = 0x00000000 \
}

#define CALCULATOR_BUTTON_COLOR \
(ui_color_t){ \
    .foreground = 0x00000000, \
    .background = 0x00FFFFFF \
}

static void calculator_draw(void)
{
    ui_draw_clear();

    ui_draw_cell(4, 10, 'C', CALCULATOR_NORMAL_COLOR);
    ui_draw_cell(4, 11, 'a', CALCULATOR_NORMAL_COLOR);
    ui_draw_cell(4, 12, 'l', CALCULATOR_NORMAL_COLOR);
    ui_draw_cell(4, 13, 'c', CALCULATOR_NORMAL_COLOR);
    ui_draw_cell(4, 14, 'u', CALCULATOR_NORMAL_COLOR);
    ui_draw_cell(4, 15, 'l', CALCULATOR_NORMAL_COLOR);
    ui_draw_cell(4, 16, 'a', CALCULATOR_NORMAL_COLOR);
    ui_draw_cell(4, 17, 't', CALCULATOR_NORMAL_COLOR);
    ui_draw_cell(4, 18, 'o', CALCULATOR_NORMAL_COLOR);
    ui_draw_cell(4, 19, 'r', CALCULATOR_NORMAL_COLOR);

    ui_draw_fill_rect(
        6,
        10,
        30,
        3,
        ' ',
        CALCULATOR_BUTTON_COLOR
    );

    ui_draw_cell(7, 15, '0', CALCULATOR_BUTTON_COLOR);

    ui_draw_cell(10, 10, '7', CALCULATOR_BUTTON_COLOR);
    ui_draw_cell(10, 14, '8', CALCULATOR_BUTTON_COLOR);
    ui_draw_cell(10, 18, '9', CALCULATOR_BUTTON_COLOR);
    ui_draw_cell(10, 22, '/', CALCULATOR_BUTTON_COLOR);

    ui_draw_cell(13, 10, '4', CALCULATOR_BUTTON_COLOR);
    ui_draw_cell(13, 14, '5', CALCULATOR_BUTTON_COLOR);
    ui_draw_cell(13, 18, '6', CALCULATOR_BUTTON_COLOR);
    ui_draw_cell(13, 22, '*', CALCULATOR_BUTTON_COLOR);

    ui_draw_cell(16, 10, '1', CALCULATOR_BUTTON_COLOR);
    ui_draw_cell(16, 14, '2', CALCULATOR_BUTTON_COLOR);
    ui_draw_cell(16, 18, '3', CALCULATOR_BUTTON_COLOR);
    ui_draw_cell(16, 22, '-', CALCULATOR_BUTTON_COLOR);

    ui_draw_cell(19, 10, 'C', CALCULATOR_BUTTON_COLOR);
    ui_draw_cell(19, 14, '=', CALCULATOR_BUTTON_COLOR);
    ui_draw_cell(19, 18, '+', CALCULATOR_BUTTON_COLOR);
}

void calculator_run(void)
{
    ui_draw_init();

    calculator_draw();

    while (!application_should_exit())
    {
        if (keyboard_has_data())
        {
            unsigned char scancode =
                keyboard_read_scancode();

            keyboard_update_state(scancode);

            if (!keyboard_is_release(scancode))
            {
                char key =
                    keyboard_scancode_to_ascii(scancode);

                if (scancode == 0x01)
                {
                    application_exit();
                }
            }
        }
    }
}
