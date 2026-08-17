#ifndef EDITOR_H
#define EDITOR_H

void editor_init(void);

unsigned int editor_get_cursor_row(void);
unsigned int editor_get_cursor_column(void);
unsigned int editor_get_preferred_column(void);

void editor_set_cursor(unsigned int row, unsigned int column);
void editor_set_preferred_column(unsigned int column);

unsigned int editor_get_line_length(unsigned int row);
int editor_has_hard_break(unsigned int row);

void editor_set_line_length(unsigned int row, unsigned int length);
void editor_set_hard_break(unsigned int row, int hard_break);

#endif
