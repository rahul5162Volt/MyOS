#include "kernel_test_ui_format.h"

static const char digits[] =
    "0123456789ABCDEF";

void kernel_test_format_uint16(
    uint16_t value,
    char* buffer
)
{
    char temp[6];
    int index = 0;
    int output = 0;

    if (value == 0)
    {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    while (value > 0)
    {
        temp[index++] =
            (char)('0' + (value % 10));

        value /= 10;
    }

    while (index > 0)
    {
        buffer[output++] =
            temp[--index];
    }

    buffer[output] = '\0';
}

void kernel_test_format_uint32_hex(
    uint32_t value,
    char* buffer
)
{
    int i;

    buffer[0] = '0';
    buffer[1] = 'x';

    for (i = 0; i < 8; ++i)
    {
        buffer[2 + i] =
            digits[(value >> (28 - (i * 4))) & 0x0F];
    }

    buffer[10] = '\0';
}
