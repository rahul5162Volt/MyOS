#define EDITOR_MAX_LINES 25
#define EDITOR_MAX_COLUMNS 80

#define VGA_MEMORY ((volatile unsigned char*)0xB8000)
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ATTRIBUTE 0x07

typedef struct
{
    char text[EDITOR_MAX_COLUMNS];
    unsigned int length;
    unsigned int hard_break;
} EditorLine;

static EditorLine editor_lines[EDITOR_MAX_LINES];

static unsigned int editor_cursor_row = 0;
static unsigned int editor_cursor_column = 0;
static unsigned int editor_preferred_column = 0;

void editor_init(void)
{
    unsigned int row = 0;

    editor_cursor_row = 0;
    editor_cursor_column = 0;
    editor_preferred_column = 0;

    while (row < EDITOR_MAX_LINES)
    {
        unsigned int column = 0;

        editor_lines[row].length = 0;
        editor_lines[row].hard_break = 0;

        while (column < EDITOR_MAX_COLUMNS)
        {
            editor_lines[row].text[column] = ' ';
            column++;
        }

        row++;
    }
}

unsigned int editor_get_cursor_row(void)
{
    return editor_cursor_row;
}

unsigned int editor_get_cursor_column(void)
{
    return editor_cursor_column;
}

unsigned int editor_get_preferred_column(void)
{
    return editor_preferred_column;
}

void editor_set_cursor(unsigned int row, unsigned int column)
{
    if (row >= EDITOR_MAX_LINES)
        row = EDITOR_MAX_LINES - 1;

    if (column >= EDITOR_MAX_COLUMNS)
        column = EDITOR_MAX_COLUMNS - 1;

    editor_cursor_row = row;
    editor_cursor_column = column;
}

void editor_set_preferred_column(unsigned int column)
{
    if (column >= EDITOR_MAX_COLUMNS)
        column = EDITOR_MAX_COLUMNS - 1;

    editor_preferred_column = column;
}

unsigned int editor_get_line_length(unsigned int row)
{
    if (row >= EDITOR_MAX_LINES)
        return 0;

    return editor_lines[row].length;
}

unsigned int editor_has_hard_break(unsigned int row)
{
    if (row >= EDITOR_MAX_LINES)
        return 0;

    return editor_lines[row].hard_break;
}

void editor_set_line_length(
    unsigned int row,
    unsigned int length
)
{
    if (row >= EDITOR_MAX_LINES)
        return;

    if (length > EDITOR_MAX_COLUMNS)
        length = EDITOR_MAX_COLUMNS;

    editor_lines[row].length = length;
}

void editor_set_hard_break(
    unsigned int row,
    unsigned int hard_break
)
{
    if (row >= EDITOR_MAX_LINES)
        return;

    editor_lines[row].hard_break =
        hard_break ? 1 : 0;
}

char editor_get_char(unsigned int row, unsigned int column)
{
    if (row >= EDITOR_MAX_LINES)
        return ' ';

    if (column >= EDITOR_MAX_COLUMNS)
        return ' ';

    return editor_lines[row].text[column];
}


void editor_set_char(
    unsigned int row,
    unsigned int column,
    char character
)
{
    if (row >= EDITOR_MAX_LINES)
        return;

    if (column >= EDITOR_MAX_COLUMNS)
        return;

    editor_lines[row].text[column] = character;
}

void editor_render(void)
{
    unsigned int row = 0;

    while (row < EDITOR_MAX_LINES &&
           row < VGA_HEIGHT)
    {
        unsigned int column = 0;
        unsigned int length =
            editor_lines[row].length;

        while (column < VGA_WIDTH)
        {
            unsigned int offset =
                (row * VGA_WIDTH + column) * 2;

            char character = ' ';

            if (column < length)
            {
                character =
                    editor_lines[row].text[column];
            }

            VGA_MEMORY[offset] =
                (unsigned char)character;

            /*
             * Software cursor.
             */
            if (row == editor_cursor_row &&
                column == editor_cursor_column)
            {
                /*
                 * Black text on white background.
                 */
                VGA_MEMORY[offset + 1] = 0x70;
            }
            else
            {
                VGA_MEMORY[offset + 1] =
                    VGA_ATTRIBUTE;
            }

            column++;
        }

        row++;
    }
}

void editor_insert_char(char character)
{
    EditorLine *line;
    unsigned int index;

    if (editor_cursor_row >= EDITOR_MAX_LINES)
        return;

    line = &editor_lines[editor_cursor_row];

    if (line->length >= EDITOR_MAX_COLUMNS)
        return;

    index = line->length;

    while (index > editor_cursor_column)
    {
        line->text[index] =
            line->text[index - 1];

        index--;
    }

    line->text[editor_cursor_column] =
        character;

    line->length++;

    editor_cursor_column++;

    editor_preferred_column =
        editor_cursor_column;
}

void editor_newline(void)
{
    if (editor_cursor_row >= EDITOR_MAX_LINES - 1)
        return;

    /*
     * The current line is terminated by Enter.
     */
    editor_lines[editor_cursor_row].hard_break = 1;

    /*
     * Move to the next line.
     */
    editor_cursor_row++;
    editor_cursor_column = 0;

    editor_preferred_column = 0;
}

void editor_cursor_left(void)
{
    EditorLine *previous_line;

    if (editor_cursor_row >= EDITOR_MAX_LINES)
        return;

    /*
     * Move normally inside the current line.
     */
    if (editor_cursor_column > 0)
    {
        editor_cursor_column--;

        editor_preferred_column =
            editor_cursor_column;

        return;
    }

    /*
     * At column 0.
     */
    if (editor_cursor_row == 0)
        return;

    previous_line =
        &editor_lines[editor_cursor_row - 1];

    /*
     * Cross the line boundary only when
     * the previous line was explicitly terminated
     * with Enter.
     */
    if (previous_line->hard_break == 0)
        return;

    editor_cursor_row--;

    /*
     * IMPORTANT:
     * Position at the actual end of the previous
     * line's text, not at VGA_WIDTH.
     */
    editor_cursor_column =
        previous_line->length;

    editor_preferred_column =
        editor_cursor_column;
}


void editor_cursor_right(void)
{
    EditorLine *line;

    if (editor_cursor_row >= EDITOR_MAX_LINES)
        return;

    line =
        &editor_lines[editor_cursor_row];

    /*
     * Normal movement within the line.
     */
    if (editor_cursor_column < line->length)
    {
        editor_cursor_column++;

        editor_preferred_column =
            editor_cursor_column;

        return;
    }

    /*
     * At the end of the line.
     * Cross to the next line only when
     * this line ends with Enter.
     */
    if (editor_cursor_column == line->length &&
        editor_cursor_row < EDITOR_MAX_LINES - 1 &&
        line->hard_break)
    {
        editor_cursor_row++;
        editor_cursor_column = 0;
        editor_preferred_column = 0;
    }
}

void editor_cursor_up(void)
{
    EditorLine *line;
    unsigned int target_column;

    if (editor_cursor_row == 0)
        return;

    /*
     * Remember the column the user wants to maintain
     * while moving vertically.
     */
    target_column =
        editor_preferred_column;

    editor_cursor_row--;

    line =
        &editor_lines[editor_cursor_row];

    if (target_column > line->length)
        target_column = line->length;

    editor_cursor_column =
        target_column;
}


void editor_cursor_down(void)
{
    EditorLine *line;
    unsigned int target_column;

    if (editor_cursor_row >= EDITOR_MAX_LINES - 1)
        return;

    target_column =
        editor_preferred_column;

    editor_cursor_row++;

    line =
        &editor_lines[editor_cursor_row];

    if (target_column > line->length)
        target_column = line->length;

    editor_cursor_column =
        target_column;
}

void editor_backspace(void)
{
    EditorLine *line;
    unsigned int index;

    if (editor_cursor_row >= EDITOR_MAX_LINES)
        return;

    line =
        &editor_lines[editor_cursor_row];

    /*
     * Normal backspace inside the current line.
     */
    if (editor_cursor_column > 0)
    {
        index =
            editor_cursor_column - 1;

        while (index < line->length - 1)
        {
            line->text[index] =
                line->text[index + 1];

            index++;
        }

        line->length--;

        line->text[line->length] = ' ';

        editor_cursor_column--;

        editor_preferred_column =
            editor_cursor_column;

        return;
    }

    /*
     * At the beginning of the first line:
     * nothing to delete.
     */
    if (editor_cursor_row == 0)
        return;

    /*
     * Join this line with the previous line.
     */
    {
        EditorLine *previous_line =
            &editor_lines[
                editor_cursor_row - 1
            ];

        unsigned int previous_length =
            previous_line->length;

        /*
         * Only merge if the previous line was
         * separated by an actual Enter.
         */
        if (!previous_line->hard_break)
            return;

        /*
         * Make sure both lines fit together.
         */
        if (previous_length + line->length >
            EDITOR_MAX_COLUMNS)
        {
            return;
        }

        /*
         * Copy current line onto the end of
         * the previous line.
         */
        index = 0;

        while (index < line->length)
        {
            previous_line->text[
                previous_length + index
            ] =
                line->text[index];

            index++;
        }

        previous_line->length =
            previous_length + line->length;

        /*
         * The previous line is no longer separated
         * from this line by Enter.
         */
        previous_line->hard_break = 0;

        /*
         * Move cursor to the old end of the
         * previous line.
         */
        editor_cursor_row--;

        editor_cursor_column =
            previous_length;

        editor_preferred_column =
            editor_cursor_column;

        /*
         * Clear the now-unused current line.
         */
        line->length = 0;
        line->hard_break = 0;

        index = 0;

        while (index < EDITOR_MAX_COLUMNS)
        {
            line->text[index] = ' ';
            index++;
        }
    }
}
