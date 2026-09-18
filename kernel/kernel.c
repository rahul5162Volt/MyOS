#include "os_startup.h"

void kernel_main(void)
{
    os_startup_run();

    while (1)
    {
        __asm__ volatile ("hlt");
    }
}
