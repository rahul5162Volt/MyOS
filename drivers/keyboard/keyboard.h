#ifndef KEYBOARD_H
#define KEYBOARD_H

unsigned char keyboard_read_scancode(void);
int keyboard_has_data(void);
int keyboard_is_release(unsigned char scancode);
char keyboard_scancode_to_ascii(unsigned char scancode);

int keyboard_is_enter(unsigned char scancode);
int keyboard_is_backspace(unsigned char scancode);
int keyboard_is_delete(unsigned char scancode);

int keyboard_is_shift_pressed(void);
int keyboard_is_shift_release(unsigned char scancode);

int keyboard_is_ctrl_pressed(void);

int keyboard_is_tab(unsigned char scancode);
void keyboard_update_state(unsigned char scancode);

int keyboard_is_arrow_left(unsigned char scancode);
int keyboard_is_arrow_right(unsigned char scancode);
int keyboard_is_arrow_up(unsigned char scancode);
int keyboard_is_arrow_down(unsigned char scancode);

int keyboard_is_home(unsigned char scancode);
int keyboard_is_end(unsigned char scancode);

#endif
