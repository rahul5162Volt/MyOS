#ifndef EDITOR_H
#define EDITOR_H

void editor_init(void);

void editor_render(
    unsigned int row,
    unsigned int column,
    unsigned int width,
    unsigned int height
);

void editor_handle_key(
    unsigned char scancode
);

#endif
