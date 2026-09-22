#ifndef KERNEL_TEST_MEMORY_H
#define KERNEL_TEST_MEMORY_H

#include <stdint.h>
#include "memory_map.h"

uint16_t kernel_test_get_memory_map_count(void);

void kernel_test_get_memory_region(
    uint16_t index,
    memory_region_t* region
);

#endif
