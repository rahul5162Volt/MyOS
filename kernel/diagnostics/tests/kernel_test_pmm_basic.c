#include "kernel_test_pmm_basic.h"

#include <stdint.h>

#include "memory.h"
#include "memory_pmm.h"
#include "kernel_test_pmm_helpers.h"

int test_page_allocation(void)
{
    void* page1;
    void* page2;
    void* page3;

    page1 = memory_allocate_page();
    page2 = memory_allocate_page();

    if (page1 == 0 || page2 == 0)
    {
        memory_free_page(page1);
        memory_free_page(page2);
        return 0;
    }

    if (!pmm_test_pages_are_aligned(
            (void*[]){ page1, page2 },
            2))
    {
        memory_free_page(page1);
        memory_free_page(page2);
        return 0;
    }

    if (page1 == page2)
    {
        memory_free_page(page1);
        memory_free_page(page2);
        return 0;
    }

    memory_free_page(page1);

    page3 = memory_allocate_page();

    if (page3 != page1)
    {
        memory_free_page(page2);
        memory_free_page(page3);
        return 0;
    }

    memory_free_page(page2);
    memory_free_page(page3);

    return 1;
}

int test_reserved_memory(void)
{
    void* reserved_pages[] =
    {
        (void*)0x8F000,
        (void*)0x90000,
        (void*)0x07FE0000
    };

    if (!pmm_test_pages_are_unavailable(
            reserved_pages,
            3))
    {
        return 0;
    }

    memory_free_page(reserved_pages[2]);

    if (memory_is_page_available(reserved_pages[2]))
    {
        return 0;
    }

    return 1;
}

int test_multiple_page_allocation(void)
{
    void* pages[16];

    for (int i = 0; i < 16; ++i)
    {
        pages[i] = memory_allocate_page();

        if (pages[i] == 0)
        {
            pmm_test_free_pages(pages, i);
            return 0;
        }
    }

    if (!pmm_test_pages_are_aligned(pages, 16))
    {
        pmm_test_free_pages(pages, 16);
        return 0;
    }

    if (!pmm_test_pages_are_unique(pages, 16))
    {
        pmm_test_free_pages(pages, 16);
        return 0;
    }

    pmm_test_free_pages(pages, 16);

    return 1;
}

int test_invalid_page_free(void)
{
    void* page;

    /*
     * NULL must be ignored.
     */
    memory_free_page(0);

    /*
     * Unaligned address must be ignored.
     */
    memory_free_page((void*)0x10001);

    /*
     * Low protected memory must be ignored.
     */
    memory_free_page((void*)0x8000);

    /*
     * Address outside the managed physical range
     * must be ignored.
     */
    memory_free_page((void*)0x100000000ULL);

    /*
     * Verify that the allocator still works afterward.
     */
    page = memory_allocate_page();

    if (page == 0)
    {
        return 0;
    }

    if (((uintptr_t)page % MEMORY_PAGE_SIZE) != 0)
    {
        memory_free_page(page);
        return 0;
    }

    memory_free_page(page);

    /*
    * Freeing the same page again must be harmless.
    */
    memory_free_page(page);

    /*
    * The page must still be available exactly once.
    */
    if (!memory_is_page_available(page))
    {
        return 0;
    }

    return 1;
}
