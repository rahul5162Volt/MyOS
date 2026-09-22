#ifndef KERNEL_TEST_UI_FORMAT_H
#define KERNEL_TEST_UI_FORMAT_H

#include <stdint.h>

void kernel_test_format_uint16(
    uint16_t value,
    char* buffer
);

void kernel_test_format_uint32_hex(
    uint32_t value,
    char* buffer
);

#endif
