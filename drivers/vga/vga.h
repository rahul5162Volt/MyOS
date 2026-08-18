#ifndef VGA_H
#define VGA_H

void vga_clear(void);
void vga_print(const char* text);
void vga_put_char(char character);
void vga_backspace(void);

void vga_update_cursor(void);

void vga_render_editor(void);

#endif
