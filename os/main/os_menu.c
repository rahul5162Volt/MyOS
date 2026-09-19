#include "os_menu.h"

#include "os_menu_screen.h"
#include "os_menu_input.h"

void os_menu_run(void)
{
    os_menu_screen_show();
    os_menu_input_run();
}
