#include "editor.h"
#include "state.h"
#include "document.h"

void editor_init(void)
{
    editor_document_init();

    editor_cursor_row = 0;
    editor_cursor_column = 0;
    editor_preferred_column = 0;

    editor_undo_group_active = 0;
    editor_undo_group_row = 0;
    editor_undo_group_column = 0;
}
