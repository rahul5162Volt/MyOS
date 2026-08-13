#include "vga/vga.h"
#include "keyboard/keyboard.h"

void kernel_main()
{
    vga_clear();
    vga_print("MyOS\n");
    vga_print("Keyboard ready.");

    while (1)
    {
        if (keyboard_has_data())
        {
            unsigned char scancode = keyboard_read_scancode();

            keyboard_update_state(scancode);

            if (!keyboard_is_release(scancode))
            {
                if (keyboard_is_arrow_left(scancode))
                    vga_cursor_left();
                else if (keyboard_is_arrow_right(scancode))
                    vga_cursor_right();
                else if (keyboard_is_arrow_up(scancode))
                    vga_cursor_up();
                else if (keyboard_is_arrow_down(scancode))
                    vga_cursor_down();
                else if (keyboard_is_tab(scancode))
                {
                    vga_put_char(' ');
                    vga_put_char(' ');
                    vga_put_char(' ');
                    vga_put_char(' ');
                }
                else if (keyboard_is_enter(scancode))
                    vga_put_char('\n');
                else if (keyboard_is_backspace(scancode))
                    vga_backspace();
                else
                {
                    char character = keyboard_scancode_to_ascii(scancode);
                    if (character != '\0')
                        vga_put_char(character);
                }
            }
        }
    }
}
