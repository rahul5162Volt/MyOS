#ifndef UI_WINDOW_H
#define UI_WINDOW_H

typedef struct
{
    unsigned int row;
    unsigned int column;

    unsigned int width;
    unsigned int height;

    const char* title;

    unsigned char border_attribute;
    unsigned char title_attribute;
} UI_Window;

void ui_window_init(
    UI_Window* window,
    unsigned int row,
    unsigned int column,
    unsigned int width,
    unsigned int height,
    const char* title
);

void ui_window_render(
    const UI_Window* window
);

unsigned int ui_window_content_row(
    const UI_Window* window
);

unsigned int ui_window_content_column(
    const UI_Window* window
);

unsigned int ui_window_content_width(
    const UI_Window* window
);

unsigned int ui_window_content_height(
    const UI_Window* window
);

#endif
