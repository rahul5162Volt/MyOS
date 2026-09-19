#include "kernel.h"

#include "kernel_panic.h"
#include "kernel_status.h"

#include "memory.h"
#include "memory_map.h"

#include "os_startup.h"

static kernel_status_t kernel_initialize(void)
{
    memory_initialize_from_bootloader();

    return KERNEL_STATUS_OK;
}

void kernel_main(void)
{
    kernel_status_t status = kernel_initialize();

    if (status != KERNEL_STATUS_OK)
    {
        kernel_panic();
    }

    os_startup_run();
}
