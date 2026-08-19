#ifndef EDITOR_H
#define EDITOR_H

void editor_init(void);

/* Cursor */
unsigned int editor_get_cursor_row(void);
unsigned int editor_get_cursor_column(void);
unsigned int editor_get_preferred_column(void);

void editor_set_cursor(unsigned int row, unsigned int column);
void editor_set_preferred_column(unsigned int column);

/* Line state */
unsigned int editor_get_line_length(unsigned int row);
unsigned int editor_has_hard_break(unsigned int row);

void editor_set_line_length(
    unsigned int row,
    unsigned int length
);

void editor_set_hard_break(
    unsigned int row,
    unsigned int hard_break
);

/* Text */
char editor_get_char(
    unsigned int row,
    unsigned int column
);

void editor_set_char(
    unsigned int row,
    unsigned int column,
    char character
);

void editor_insert_char(char character);
void editor_insert_newline(void);
void editor_delete_backward(void);

void editor_cursor_left(void);
void editor_cursor_right(void);
void editor_cursor_up(void);
void editor_cursor_down(void);

void editor_render(void);

#endif
