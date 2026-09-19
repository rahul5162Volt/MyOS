#include "os_startup.h"

#include "os_startup_screen.h"
#include "os_main.h"

void os_startup_run(void)
{
    os_startup_screen_show();

    os_main_run();
}
