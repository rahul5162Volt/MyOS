#include "kernel_test_pmm_advanced.h"

#include <stdint.h>

#include "memory.h"
#include "memory_pmm.h"
#include "kernel_test_pmm_helpers.h"

int test_multiple_page_reuse(void)
{
    void* first[8];
    void* second[8];

    for (int i = 0; i < 8; ++i)
    {
        first[i] = memory_allocate_page();

        if (first[i] == 0)
        {
            pmm_test_free_pages(first, i);
            return 0;
        }
    }

    if (!pmm_test_pages_are_aligned(first, 8))
    {
        pmm_test_free_pages(first, 8);
        return 0;
    }

    pmm_test_free_pages(first, 8);

    for (int i = 0; i < 8; ++i)
    {
        second[i] = memory_allocate_page();

        if (second[i] == 0)
        {
            pmm_test_free_pages(second, i);
            return 0;
        }
    }

    if (!pmm_test_pages_are_aligned(second, 8))
    {
        pmm_test_free_pages(second, 8);
        return 0;
    }

    if (!pmm_test_pages_are_unique(second, 8))
    {
        pmm_test_free_pages(second, 8);
        return 0;
    }

    pmm_test_free_pages(second, 8);

    return 1;
}

int test_page_fragmentation(void)
{
    void* pages[16];
    void* reused[8];

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

    for (int i = 0; i < 16; i += 2)
    {
        memory_free_page(pages[i]);
    }

    for (int i = 0; i < 8; ++i)
    {
        reused[i] = memory_allocate_page();

        if (reused[i] == 0)
        {
            pmm_test_free_pages(reused, i);

            for (int j = 1; j < 16; j += 2)
            {
                memory_free_page(pages[j]);
            }

            return 0;
        }
    }

    if (!pmm_test_pages_are_aligned(reused, 8))
    {
        pmm_test_free_pages(reused, 8);

        for (int i = 1; i < 16; i += 2)
        {
            memory_free_page(pages[i]);
        }

        return 0;
    }

    if (!pmm_test_pages_are_unique(reused, 8))
    {
        pmm_test_free_pages(reused, 8);

        for (int i = 1; i < 16; i += 2)
        {
            memory_free_page(pages[i]);
        }

        return 0;
    }

    for (int i = 1; i < 16; i += 2)
    {
        memory_free_page(pages[i]);
    }

    pmm_test_free_pages(reused, 8);

    return 1;
}

int test_pmm_stress(void)
{
    enum
    {
        TEST_PAGE_COUNT = 64
    };

    void* pages[TEST_PAGE_COUNT];

    for (uint32_t i = 0; i < TEST_PAGE_COUNT; ++i)
    {
        pages[i] = memory_allocate_page();

        if (pages[i] == 0)
        {
            pmm_test_free_pages(pages, i);
            return 0;
        }
    }

    if (!pmm_test_pages_are_aligned(
            pages,
            TEST_PAGE_COUNT))
    {
        pmm_test_free_pages(
            pages,
            TEST_PAGE_COUNT);

        return 0;
    }

    if (!pmm_test_pages_are_unavailable(
            pages,
            TEST_PAGE_COUNT))
    {
        pmm_test_free_pages(
            pages,
            TEST_PAGE_COUNT);

        return 0;
    }

    pmm_test_free_pages(
        pages,
        TEST_PAGE_COUNT);

    if (!pmm_test_pages_are_available(
            pages,
            TEST_PAGE_COUNT))
    {
        return 0;
    }

    return 1;
}
