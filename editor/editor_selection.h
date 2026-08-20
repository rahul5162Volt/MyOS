#ifndef EDITOR_SELECTION_H
#define EDITOR_SELECTION_H

void editor_selection_start(void);
void editor_selection_update(void);
void editor_selection_clear(void);

unsigned int editor_selection_is_active(void);

int editor_selection_contains(
    unsigned int row,
    unsigned int column
);

void editor_selection_to_home(void);
void editor_selection_to_end(void);

void editor_selection_delete(void);

void editor_selection_all(void);

void editor_selection_to_document_start(void);
void editor_selection_to_document_end(void);

unsigned int editor_selection_has_anchor(void);

#endif
