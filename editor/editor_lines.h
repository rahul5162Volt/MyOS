#ifndef EDITOR_LINES_H
#define EDITOR_LINES_H

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

void editor_newline(void);

void editor_backspace(void);

#endif