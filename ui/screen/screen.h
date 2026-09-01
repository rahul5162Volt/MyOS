#ifndef UI_SCREEN_H
#define UI_SCREEN_H

#include "layout.h"
#include "window.h"
#include "ui_text.h"

void ui_screen_init(void);

const UI_Panel* ui_screen_get_header_panel(void);

const UI_Window* ui_screen_get_editor_window(void);

const UI_Panel* ui_screen_get_status_panel(void);

const UI_Text* ui_screen_get_header_title(void);

const UI_Text* ui_screen_get_header_version(void);

const UI_Text* ui_screen_get_status_text(void);

#endif
