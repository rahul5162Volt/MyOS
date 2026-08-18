#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#define EDITOR_MAX_LINES 25
#define EDITOR_MAX_COLUMNS 80

typedef struct
{
    char text[EDITOR_MAX_COLUMNS];
    unsigned int length;
    unsigned char hard_break;
} EditorLine;

extern EditorLine editor_lines[EDITOR_MAX_LINES];

extern unsigned int editor_cursor_row;
extern unsigned int editor_cursor_column;
extern unsigned int editor_preferred_column;

#endif
