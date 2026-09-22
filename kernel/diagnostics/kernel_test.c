#include "kernel_test.h"

#include "tests/kernel_test_memory.h"
#include "tests/kernel_test_pmm_basic.h"
#include "tests/kernel_test_pmm_advanced.h"
#include "ui/kernel_test_ui.h"

void kernel_test_run(void)
{
    kernel_test_ui_init();

    kernel_test_ui_title(
        "Kernel Diagnostics"
    );

    kernel_test_ui_section(
        "Memory Tests"
    );

    kernel_test_ui_test(
        "Page allocation",
        test_page_allocation()
    );

    kernel_test_ui_test(
        "Reserved memory",
        test_reserved_memory()
    );

    kernel_test_ui_test(
        "Multiple allocation",
        test_multiple_page_allocation()
    );

    kernel_test_ui_test(
        "Multiple page reuse",
        test_multiple_page_reuse()
    );

    kernel_test_ui_test(
        "Invalid page free",
        test_invalid_page_free()
    );

    kernel_test_ui_test(
        "Page fragmentation",
        test_page_fragmentation()
    );

    kernel_test_ui_test(
        "PMM stress",
        test_pmm_stress()
    );

    kernel_test_ui_count(
        "E820 Memory Map",
        kernel_test_get_memory_map_count()
    );

    for (uint16_t i = 0;
         i < kernel_test_get_memory_map_count();
         ++i)
    {
        memory_region_t region;

        kernel_test_get_memory_region(
            i,
            &region
        );

        kernel_test_ui_memory_region(
            i,
            &region
        );
    }

    kernel_test_ui_status(
        "All tests completed"
    );

    while (1)
    {
        __asm__ volatile ("cli");
        __asm__ volatile ("hlt");
    }
}
