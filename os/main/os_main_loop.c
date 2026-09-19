#include "os_main_loop.h"

#include "os_menu.h"

void os_main_loop_run(void)
{
    while (1)
    {
        os_menu_run();
    }
}
