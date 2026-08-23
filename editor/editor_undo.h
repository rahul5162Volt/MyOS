#ifndef EDITOR_UNDO_H
#define EDITOR_UNDO_H

void editor_undo_init(void);

void editor_undo_save(void);

unsigned int editor_undo_can_undo(void);

void editor_undo(void);

#endif
