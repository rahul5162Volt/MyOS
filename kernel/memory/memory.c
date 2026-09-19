#include "memory.h"

extern unsigned char kernel_end;

#define BOOT_MEMORY_MAP_ADDRESS       0x0000A000
#define BOOT_MEMORY_MAP_COUNT_ADDRESS 0x0000AFF0

#define MEMORY_REGION_USABLE 1

#define MEMORY_PAGE_SIZE 4096

static uintptr_t memory_align_up(uintptr_t address)
{
    return (address + MEMORY_PAGE_SIZE - 1) &
           ~(MEMORY_PAGE_SIZE - 1);
}

static uintptr_t memory_next_free;
static uintptr_t memory_end;

void memory_initialize(
    const memory_region_t* regions,
    uint32_t region_count
)
{
    memory_next_free =
        memory_align_up((uintptr_t)&kernel_end);
    
    memory_end = 0;

    for (uint32_t i = 0; i < region_count; ++i)
    {
        const memory_region_t* region = &regions[i];

        if (region->type != MEMORY_REGION_USABLE)
        {
            continue;
        }

        uintptr_t region_start = (uintptr_t)region->base;
        uintptr_t region_end =
            (uintptr_t)(region->base + region->length);

        if (memory_next_free >= region_start &&
            memory_next_free < region_end)
        {
            memory_end = region_end;
            break;
        }
    }

    if (regions == 0 || region_count == 0)
    {
        return;
    }

    for (uint32_t i = 0; i < region_count; ++i)
    {
        const memory_region_t* region = &regions[i];

        if (region->length == 0)
        {
            continue;
        }

        if (region->type != MEMORY_REGION_USABLE)
        {
            continue;
        }

        /*
         * Usable physical-memory region.
         * Allocation will be implemented later.
         */
        (void)region;
    }
}

void memory_initialize_from_bootloader(void)
{
    const memory_region_t* memory_map =
        (const memory_region_t*)BOOT_MEMORY_MAP_ADDRESS;

    const uint32_t memory_map_count =
        *(const uint16_t*)BOOT_MEMORY_MAP_COUNT_ADDRESS;

    memory_initialize(memory_map, memory_map_count);
}

void* memory_allocate(uint32_t size)
{
    if (size == 0)
    {
        return 0;
    }

    size = (size + MEMORY_PAGE_SIZE - 1) &
           ~(MEMORY_PAGE_SIZE - 1);

    uintptr_t address = memory_next_free;
    uintptr_t next = address + size;

    if (next > memory_end)
    {
        return 0;
    }

    memory_next_free = next;

    return (void*)address;
}

void* memory_allocate_page(void)
{
    return memory_allocate(MEMORY_PAGE_SIZE);
}

void memory_free_page(void* address)
{
    memory_free(address);
}

void memory_free(void* address)
{
    (void)address;
}
