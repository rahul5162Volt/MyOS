#ifndef EDITOR_TEXT_H
#define EDITOR_TEXT_H

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

#endif