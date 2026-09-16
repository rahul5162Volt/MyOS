#include "ui_framebuffer_backend.h"

#include "video/font.h"
#include "video/renderer.h"
#include "video/video_info.h"

static unsigned int ui_framebuffer_columns;
static unsigned int ui_framebuffer_rows;

void ui_framebuffer_backend_init(void)
{
    video_info_t* video =
        (video_info_t*)VIDEO_INFO_ADDRESS;

    renderer_init(
        video->framebuffer,
        video->pitch,
        video->width,
        video->height,
        video->bpp
    );

    ui_framebuffer_columns =
        video->width / FONT_CELL_WIDTH;

    ui_framebuffer_rows =
        video->height / FONT_CELL_HEIGHT;
}

unsigned int ui_framebuffer_backend_get_width(void)
{
    return ui_framebuffer_columns;
}

unsigned int ui_framebuffer_backend_get_height(void)
{
    return ui_framebuffer_rows;
}

void ui_framebuffer_backend_clear(void)
{
    renderer_clear(0x00000000);
}

void ui_framebuffer_backend_draw_cell(
    unsigned int row,
    unsigned int column,
    char character,
    ui_color_t color
)
{
    unsigned int x;
    unsigned int y;

    if (column >= ui_framebuffer_columns ||
        row >= ui_framebuffer_rows)
    {
        return;
    }

    x = column * FONT_CELL_WIDTH;
    y = row * FONT_CELL_HEIGHT;

    renderer_fill_rect(
        x,
        y,
        FONT_CELL_WIDTH,
        FONT_CELL_HEIGHT,
        color.background
    );

    font_draw_char(
        x,
        y,
        character,
        color.foreground
    );
}
