#ifndef KERNEL_TEST_UI_H
#define KERNEL_TEST_UI_H

#include <stdint.h>

#include "memory_map.h"

void kernel_test_ui_init(void);

void kernel_test_ui_title(
    const char* text
);

void kernel_test_ui_section(
    const char* text
);

void kernel_test_ui_test(
    const char* label,
    int passed
);

void kernel_test_ui_count(
    const char* label,
    uint16_t count
);

void kernel_test_ui_memory_region(
    uint16_t index,
    const memory_region_t* region
);

void kernel_test_ui_status(
    const char* text
);

#endif
