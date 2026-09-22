#ifndef KERNEL_TEST_PMM_HELPERS_H
#define KERNEL_TEST_PMM_HELPERS_H

#include <stdint.h>

int pmm_test_pages_are_aligned(
    void* pages[],
    uint32_t count
);

int pmm_test_pages_are_unique(
    void* pages[],
    uint32_t count
);

void pmm_test_free_pages(
    void* pages[],
    uint32_t count
);

int pmm_test_pages_are_available(
    void* pages[],
    uint32_t count
);

int pmm_test_pages_are_unavailable(
    void* pages[],
    uint32_t count
);

#endif
