#include "document.h"
#include "state.h"

void editor_document_init(void)
{
    unsigned int row = 0;

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
