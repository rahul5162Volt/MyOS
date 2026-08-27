#ifndef VGA_H
#define VGA_H

#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define VGA_DEFAULT_ATTRIBUTE 0x07

void vga_clear(void);
void vga_print(const char* text);
void vga_put_char(char character);
void vga_print_hex8(unsigned char value);

void vga_write_cell(
    unsigned int row,
    unsigned int column,
    char character,
    unsigned char attribute
);

#endif
