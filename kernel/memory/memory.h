#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#include "memory_map.h"

#define MEMORY_PAGE_SIZE 4096

void* memory_allocate_page(void);
void memory_free_page(void* address);

void memory_initialize(
    const memory_region_t* regions,
    uint32_t region_count
);

void memory_initialize_from_bootloader(void);

void* memory_allocate(uint32_t size);
void memory_free(void* address);

#endif
