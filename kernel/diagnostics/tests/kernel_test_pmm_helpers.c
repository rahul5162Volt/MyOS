#include "kernel_test_pmm_helpers.h"

#include <stdint.h>

#include "memory.h"

int pmm_test_pages_are_aligned(
    void* pages[],
    uint32_t count
)
{
    for (uint32_t i = 0; i < count; ++i)
    {
        if (pages[i] == 0)
        {
            return 0;
        }

        if (((uintptr_t)pages[i] % MEMORY_PAGE_SIZE) != 0)
        {
            return 0;
        }
    }

    return 1;
}

int pmm_test_pages_are_unique(
    void* pages[],
    uint32_t count
)
{
    for (uint32_t i = 0; i < count; ++i)
    {
        for (uint32_t j = i + 1; j < count; ++j)
        {
            if (pages[i] == pages[j])
            {
                return 0;
            }
        }
    }

    return 1;
}

void pmm_test_free_pages(
    void* pages[],
    uint32_t count
)
{
    for (uint32_t i = 0; i < count; ++i)
    {
        memory_free_page(pages[i]);
    }
}

int pmm_test_pages_are_available(
    void* pages[],
    uint32_t count
)
{
    for (uint32_t i = 0; i < count; ++i)
    {
        if (!memory_is_page_available(pages[i]))
        {
            return 0;
        }
    }

    return 1;
}

int pmm_test_pages_are_unavailable(
    void* pages[],
    uint32_t count
)
{
    for (uint32_t i = 0; i < count; ++i)
    {
        if (memory_is_page_available(pages[i]))
        {
            return 0;
        }
    }

    return 1;
}
