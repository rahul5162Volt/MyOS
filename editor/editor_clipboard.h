#ifndef EDITOR_CLIPBOARD_H
#define EDITOR_CLIPBOARD_H

void editor_clipboard_clear(void);

unsigned int editor_clipboard_has_data(void);

void editor_clipboard_copy_selection(void);

void editor_clipboard_paste(void);

#endif
