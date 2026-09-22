#include "kernel_test_ui.h"

#include "kernel_test_ui_config.h"
#include "kernel_test_ui_format.h"

#include "framebuffer.h"
#include "font.h"

static uint16_t kernel_test_ui_test_y;

void kernel_test_ui_init(void)
{
    framebuffer_clear(
        KERNEL_TEST_BACKGROUND
    );

    /* Reset test row position. */
    kernel_test_ui_test_y =
        KERNEL_TEST_TEST_START_Y;
}

void kernel_test_ui_title(
    const char* text
)
{
    font_draw_string_scaled(
        KERNEL_TEST_MARGIN_X,
        KERNEL_TEST_TITLE_Y,
        text,
        KERNEL_TEST_TITLE_COLOR,
        KERNEL_TEST_TITLE_SCALE
    );
}

void kernel_test_ui_section(
    const char* text
)
{
    font_draw_string_scaled(
        KERNEL_TEST_MARGIN_X,
        KERNEL_TEST_SECTION_Y,
        text,
        KERNEL_TEST_SECTION_COLOR,
        KERNEL_TEST_SECTION_SCALE
    );
}

void kernel_test_ui_test(
    const char* label,
    int passed
)
{
    uint16_t y =
        kernel_test_ui_test_y;

    font_draw_string_scaled(
        KERNEL_TEST_MARGIN_X,
        y,
        label,
        KERNEL_TEST_LABEL_COLOR,
        KERNEL_TEST_LABEL_SCALE
    );

    font_draw_string_scaled(
        KERNEL_TEST_MARGIN_X + 480,
        y,
        passed ? "PASS" : "FAIL",
        passed
            ? KERNEL_TEST_VALUE_PASS_COLOR
            : KERNEL_TEST_VALUE_FAIL_COLOR,
        KERNEL_TEST_VALUE_SCALE
    );

    kernel_test_ui_test_y +=
        KERNEL_TEST_TEST_ROW_HEIGHT;
}

void kernel_test_ui_count(
    const char* label,
    uint16_t count
)
{
    char count_text[6];

    kernel_test_format_uint16(
        count,
        count_text
    );

    font_draw_string_scaled(
        KERNEL_TEST_MARGIN_X,
        KERNEL_TEST_E820_Y,
        label,
        KERNEL_TEST_LABEL_COLOR,
        KERNEL_TEST_LABEL_SCALE
    );

    font_draw_string_scaled(
        KERNEL_TEST_MARGIN_X + 480,
        KERNEL_TEST_E820_Y,
        count_text,
        KERNEL_TEST_VALUE_PASS_COLOR,
        KERNEL_TEST_VALUE_SCALE
    );
}

void kernel_test_ui_memory_region(
    uint16_t index,
    const memory_region_t* region
)
{
    char index_text[6];
    char base_text[11];
    char length_text[11];
    char type_text[6];

    kernel_test_format_uint16(
        index,
        index_text
    );

    kernel_test_format_uint32_hex(
        (uint32_t)region->base,
        base_text
    );

    kernel_test_format_uint32_hex(
        (uint32_t)region->length,
        length_text
    );

    kernel_test_format_uint16(
        (uint16_t)region->type,
        type_text
    );

    uint16_t y =
        KERNEL_TEST_E820_REGION_Y +
        (index * KERNEL_TEST_E820_REGION_HEIGHT);

    font_draw_string_scaled(
        KERNEL_TEST_MARGIN_X,
        y,
        "Region",
        KERNEL_TEST_LABEL_COLOR,
        KERNEL_TEST_LABEL_SCALE
    );

    font_draw_string_scaled(
        KERNEL_TEST_MARGIN_X + 120,
        y,
        index_text,
        KERNEL_TEST_LABEL_COLOR,
        KERNEL_TEST_LABEL_SCALE
    );

    font_draw_string_scaled(
        KERNEL_TEST_MARGIN_X + 180,
        y,
        base_text,
        KERNEL_TEST_VALUE_PASS_COLOR,
        KERNEL_TEST_VALUE_SCALE
    );

    font_draw_string_scaled(
        KERNEL_TEST_MARGIN_X + 440,
        y,
        length_text,
        KERNEL_TEST_VALUE_PASS_COLOR,
        KERNEL_TEST_VALUE_SCALE
    );

    font_draw_string_scaled(
        KERNEL_TEST_MARGIN_X + 700,
        y,
        type_text,
        KERNEL_TEST_VALUE_PASS_COLOR,
        KERNEL_TEST_VALUE_SCALE
    );
}

void kernel_test_ui_status(
    const char* text
)
{
    font_draw_string_scaled(
        KERNEL_TEST_MARGIN_X,
        KERNEL_TEST_STATUS_Y,
        text,
        KERNEL_TEST_STATUS_COLOR,
        KERNEL_TEST_STATUS_SCALE
    );
}
