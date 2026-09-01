#include "vga.h"
#include "io.h"

#define VGA_MEMORY ((volatile unsigned char*)0xB8000)

static unsigned int vga_cursor = 0;

void vga_write_cell(
    unsigned int row,
    unsigned int column,
    char character,
    unsigned char attribute
)
{
    unsigned int offset =
        (row * VGA_WIDTH + column) * 2;

    VGA_MEMORY[offset] = character;
    VGA_MEMORY[offset + 1] = attribute;
}

void vga_clear(void)
{
    vga_clear_region(
        0,
        0,
        VGA_WIDTH,
        VGA_HEIGHT
    );

    vga_cursor = 0;
}

void vga_clear_region(
    unsigned int row,
    unsigned int column,
    unsigned int width,
    unsigned int height
)
{
    unsigned int current_row = 0;

    while (current_row < height)
    {
        unsigned int current_column = 0;

        while (current_column < width)
        {
            vga_write_cell(
                row + current_row,
                column + current_column,
                ' ',
                VGA_DEFAULT_ATTRIBUTE
            );

            current_column++;
        }

        current_row++;
    }
}

void vga_put_char(char character)
{
    unsigned int row;
    unsigned int column;

    if (character == '\n')
    {
        vga_cursor +=
            VGA_WIDTH -
            (vga_cursor % VGA_WIDTH);

        if (vga_cursor >= VGA_WIDTH * VGA_HEIGHT)
        {
            vga_cursor = 0;
        }

        return;
    }

    if (character == '\r')
    {
        vga_cursor -=
            vga_cursor % VGA_WIDTH;

        return;
    }

    row = vga_cursor / VGA_WIDTH;
    column = vga_cursor % VGA_WIDTH;

    vga_write_cell(
        row,
        column,
        character,
        VGA_DEFAULT_ATTRIBUTE
    );

    vga_cursor++;

    if (vga_cursor >= VGA_WIDTH * VGA_HEIGHT)
    {
        vga_cursor = 0;
    }
}

void vga_print(const char* text)
{
    while (*text != '\0')
    {
        vga_put_char(*text);
        text++;
    }
}

void vga_print_hex8(unsigned char value)
{
    const char* hex =
        "0123456789ABCDEF";

    char output[3];

    output[0] =
        hex[(value >> 4) & 0x0F];

    output[1] =
        hex[value & 0x0F];

    output[2] = '\0';

    vga_print(output);
}

void vga_disable_cursor(void)
{
    unsigned char cursor_start;

    outb(0x3D4, 0x0A);

    cursor_start = inb(0x3D5);

    outb(
        0x3D4,
        0x0A
    );

    outb(
        0x3D5,
        cursor_start | 0x20
    );
}
