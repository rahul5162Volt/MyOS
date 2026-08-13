#ifndef VGA_H
#define VGA_H

void vga_clear(void);
void vga_print(const char* text);
void vga_put_char(char character);
void vga_backspace(void);

void vga_cursor_left(void);
void vga_cursor_right(void);
void vga_cursor_up(void);
void vga_cursor_down(void);

void vga_update_cursor(void);

#endif
