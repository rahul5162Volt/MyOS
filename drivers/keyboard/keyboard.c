#include "keyboard.h"

#define KEYBOARD_DATA_PORT   0x60
#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_EXTENDED_PREFIX 0xE0

#define KEYBOARD_LEFT_SHIFT_SCANCODE  0x2A
#define KEYBOARD_RIGHT_SHIFT_SCANCODE 0x36
#define KEYBOARD_LEFT_SHIFT_RELEASE   0xAA
#define KEYBOARD_RIGHT_SHIFT_RELEASE  0xB6

#define KEYBOARD_CAPS_LOCK_SCANCODE   0x3A
#define KEYBOARD_CAPS_LOCK_RELEASE    0xBA

#define KEYBOARD_LEFT_CTRL_SCANCODE  0x1D
#define KEYBOARD_LEFT_CTRL_RELEASE   0x9D

#define KEYBOARD_ARROW_LEFT   0x4B
#define KEYBOARD_ARROW_RIGHT  0x4D
#define KEYBOARD_ARROW_UP     0x48
#define KEYBOARD_ARROW_DOWN   0x50

#define KEYBOARD_DELETE 0x53

#define KEYBOARD_HOME 0x47
#define KEYBOARD_END  0x4F

static int keyboard_left_shift_pressed = 0;
static int keyboard_right_shift_pressed = 0;

static int keyboard_caps_lock = 0;
static int keyboard_extended = 0;

static int keyboard_left_ctrl_pressed = 0;

static unsigned char inb(unsigned short port)
{
    unsigned char value;
    __asm__ volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

static unsigned char keyboard_read_status(void)
{
    return inb(KEYBOARD_STATUS_PORT);
}

int keyboard_has_data(void)
{
    return (keyboard_read_status() & 0x01) != 0;
}

unsigned char keyboard_read_scancode(void)
{
    while ((keyboard_read_status() & 0x01) == 0)
    {
    }

    unsigned char scancode = inb(KEYBOARD_DATA_PORT);

    if (scancode == KEYBOARD_EXTENDED_PREFIX)
    {
        keyboard_extended = 1;

        while ((keyboard_read_status() & 0x01) == 0)
        {
        }

        scancode = inb(KEYBOARD_DATA_PORT);
        keyboard_extended = 0;
        return scancode;
    }

    return scancode;
}

int keyboard_is_release(unsigned char scancode)
{
    return (scancode & 0x80) != 0;
}

char keyboard_scancode_to_ascii(unsigned char scancode)
{
    static const char normal[128] = {
        [0x02] = '1', [0x03] = '2', [0x04] = '3', [0x05] = '4',
        [0x06] = '5', [0x07] = '6', [0x08] = '7', [0x09] = '8',
        [0x0A] = '9', [0x0B] = '0', [0x0C] = '-', [0x0D] = '=',
        [0x10] = 'q', [0x11] = 'w', [0x12] = 'e', [0x13] = 'r',
        [0x14] = 't', [0x15] = 'y', [0x16] = 'u', [0x17] = 'i',
        [0x18] = 'o', [0x19] = 'p', [0x1A] = '[', [0x1B] = ']',
        [0x1E] = 'a', [0x1F] = 's', [0x20] = 'd', [0x21] = 'f',
        [0x22] = 'g', [0x23] = 'h', [0x24] = 'j', [0x25] = 'k',
        [0x26] = 'l', [0x27] = ';', [0x28] = '\'', [0x29] = '`',
        [0x2B] = '\\', [0x2C] = 'z', [0x2D] = 'x', [0x2E] = 'c',
        [0x2F] = 'v', [0x30] = 'b', [0x31] = 'n', [0x32] = 'm',
        [0x33] = ',', [0x34] = '.', [0x35] = '/', [0x39] = ' '
    };

    static const char shifted[128] = {
        [0x02] = '!', [0x03] = '@', [0x04] = '#', [0x05] = '$',
        [0x06] = '%', [0x07] = '^', [0x08] = '&', [0x09] = '*',
        [0x0A] = '(', [0x0B] = ')', [0x0C] = '_', [0x0D] = '+',
        [0x10] = 'Q', [0x11] = 'W', [0x12] = 'E', [0x13] = 'R',
        [0x14] = 'T', [0x15] = 'Y', [0x16] = 'U', [0x17] = 'I',
        [0x18] = 'O', [0x19] = 'P', [0x1A] = '{', [0x1B] = '}',
        [0x1E] = 'A', [0x1F] = 'S', [0x20] = 'D', [0x21] = 'F',
        [0x22] = 'G', [0x23] = 'H', [0x24] = 'J', [0x25] = 'K',
        [0x26] = 'L', [0x27] = ':', [0x28] = '"', [0x29] = '~',
        [0x2B] = '|', [0x2C] = 'Z', [0x2D] = 'X', [0x2E] = 'C',
        [0x2F] = 'V', [0x30] = 'B', [0x31] = 'N', [0x32] = 'M',
        [0x33] = '<', [0x34] = '>', [0x35] = '?', [0x39] = ' '
    };

    if (scancode >= 128)
        return '\0';

    int shift_pressed = keyboard_left_shift_pressed || keyboard_right_shift_pressed;
    int is_letter =
        (scancode >= 0x10 && scancode <= 0x19) ||
        (scancode >= 0x1E && scancode <= 0x26) ||
        (scancode >= 0x2C && scancode <= 0x32);

    if (is_letter)
    {
        int uppercase = shift_pressed != keyboard_caps_lock;
        return uppercase ? shifted[scancode] : normal[scancode];
    }

    return shift_pressed ? shifted[scancode] : normal[scancode];
}

int keyboard_is_enter(unsigned char scancode) { return scancode == 0x1C; }
int keyboard_is_backspace(unsigned char scancode) { return scancode == 0x0E; }
int keyboard_is_delete(unsigned char scancode) { return scancode == KEYBOARD_DELETE; }

int keyboard_is_shift_pressed(void)
{
    return keyboard_left_shift_pressed ||
           keyboard_right_shift_pressed;
}
int keyboard_is_shift_release(unsigned char scancode)
{
    return scancode == KEYBOARD_LEFT_SHIFT_RELEASE || scancode == KEYBOARD_RIGHT_SHIFT_RELEASE;
}
int keyboard_is_tab(unsigned char scancode) { return scancode == 0x0F; }

void keyboard_update_state(unsigned char scancode)
{
    if (scancode == KEYBOARD_LEFT_SHIFT_SCANCODE)
        keyboard_left_shift_pressed = 1;
    else if (scancode == KEYBOARD_RIGHT_SHIFT_SCANCODE)
        keyboard_right_shift_pressed = 1;
    else if (scancode == KEYBOARD_LEFT_SHIFT_RELEASE)
        keyboard_left_shift_pressed = 0;
    else if (scancode == KEYBOARD_RIGHT_SHIFT_RELEASE)
        keyboard_right_shift_pressed = 0;
    else if (scancode == KEYBOARD_CAPS_LOCK_SCANCODE)
        keyboard_caps_lock = !keyboard_caps_lock;
    else if (scancode == KEYBOARD_LEFT_CTRL_SCANCODE)
        keyboard_left_ctrl_pressed = 1;
    else if (scancode == KEYBOARD_LEFT_CTRL_RELEASE)
        keyboard_left_ctrl_pressed = 0;
}

int keyboard_is_arrow_left(unsigned char scancode) { return scancode == KEYBOARD_ARROW_LEFT; }
int keyboard_is_arrow_right(unsigned char scancode) { return scancode == KEYBOARD_ARROW_RIGHT; }
int keyboard_is_arrow_up(unsigned char scancode) { return scancode == KEYBOARD_ARROW_UP; }
int keyboard_is_arrow_down(unsigned char scancode) { return scancode == KEYBOARD_ARROW_DOWN; }

int keyboard_is_home(unsigned char scancode)
{
    return scancode == KEYBOARD_HOME;
}

int keyboard_is_end(unsigned char scancode)
{
    return scancode == KEYBOARD_END;
}

int keyboard_is_ctrl_pressed(void)
{
    return keyboard_left_ctrl_pressed;
}