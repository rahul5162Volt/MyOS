#include "editor.h"
#include "editor_state.h"
#include "editor_text.h"
#include "editor_cursor.h"
#include "editor_lines.h"
#include "editor_render.h"
#include "editor_navigation.h"
#include "editor_edit.h"

#define EDITOR_MAX_LINES 25
#define EDITOR_MAX_COLUMNS 80

#define VGA_MEMORY ((volatile unsigned char*)0xB8000)
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ATTRIBUTE 0x07

EditorLine editor_lines[EDITOR_MAX_LINES];

unsigned int editor_cursor_row = 0;
unsigned int editor_cursor_column = 0;
unsigned int editor_preferred_column = 0;

void editor_init(void)
{
    unsigned int row = 0;

    editor_cursor_row = 0;
    editor_cursor_column = 0;
    editor_preferred_column = 0;

    while (row < EDITOR_MAX_LINES)
    {
        unsigned int column = 0;

        editor_lines[row].length = 0;
        editor_lines[row].hard_break = 0;

        while (column < EDITOR_MAX_COLUMNS)
        {
            editor_lines[row].text[column] = ' ';
            column++;
        }

        row++;
    }
}
