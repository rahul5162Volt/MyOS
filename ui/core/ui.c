#include "ui.h"
#include "screen.h"
#include "render.h"

void ui_init(void)
{
    ui_screen_init();
}

void ui_render(void)
{
    ui_renderer_render();
}
