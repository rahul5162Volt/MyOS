#include "os_startup_wait.h"

void os_startup_wait(void)
{
    volatile unsigned long delay;

    for (delay = 0; delay < 250000000UL; delay++)
    {
        __asm__ volatile ("nop");
    }
}
