#include "kernel_test_memory.h"

#include <stdint.h>

#include "memory_map.h"

uint16_t kernel_test_get_memory_map_count(void)
{
    return *(const uint16_t*)0xAFF0;
}

void kernel_test_get_memory_region(
    uint16_t index,
    memory_region_t* region
)
{
    const memory_region_t* memory_map =
        (const memory_region_t*)0xA000;

    *region = memory_map[index];
}
