#include "kernel_panic.h"

void kernel_panic(void)
{
    __asm__ volatile ("cli");

    while (1)
    {
        __asm__ volatile ("hlt");
    }
}
