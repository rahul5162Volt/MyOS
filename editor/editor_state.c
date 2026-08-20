#include "editor_state.h"

EditorLine editor_lines[EDITOR_MAX_LINES];

unsigned int editor_cursor_row = 0;
unsigned int editor_cursor_column = 0;
unsigned int editor_preferred_column = 0;

unsigned int editor_selection_active = 0;

unsigned int editor_selection_anchor_row = 0;
unsigned int editor_selection_anchor_column = 0;
unsigned int editor_selection_anchor_active = 0;
