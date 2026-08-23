#include "editor_undo.h"
#include "editor_state.h"

#define EDITOR_UNDO_MAX 4
#define EDITOR_REDO_MAX 4

typedef struct
{
    EditorLine lines[EDITOR_MAX_LINES];

    unsigned int cursor_row;
    unsigned int cursor_column;
    unsigned int preferred_column;
} EditorUndoSnapshot;

static EditorUndoSnapshot
editor_undo_history[EDITOR_UNDO_MAX];

static unsigned int
editor_undo_count = 0;

static EditorUndoSnapshot
editor_redo_history[EDITOR_REDO_MAX];

static unsigned int
editor_redo_count = 0;

void editor_undo_init(void)
{
    editor_undo_count = 0;
    editor_redo_count = 0;
}

void editor_undo_save(void)
{
    unsigned int row;

    editor_redo_count = 0;

    /*
     * If the history is full, discard
     * the oldest snapshot.
     */
    if (editor_undo_count >= EDITOR_UNDO_MAX)
    {
        row = 1;

        while (row < EDITOR_UNDO_MAX)
        {
            editor_undo_history[row - 1] =
                editor_undo_history[row];

            row++;
        }

        editor_undo_count =
            EDITOR_UNDO_MAX - 1;
    }

    /*
     * Save the complete editor state.
     */
    row = 0;

    while (row < EDITOR_MAX_LINES)
    {
        editor_undo_history[
            editor_undo_count
        ].lines[row] =
            editor_lines[row];

        row++;
    }

    editor_undo_history[
        editor_undo_count
    ].cursor_row =
        editor_cursor_row;

    editor_undo_history[
        editor_undo_count
    ].cursor_column =
        editor_cursor_column;

    editor_undo_history[
        editor_undo_count
    ].preferred_column =
        editor_preferred_column;

    editor_undo_count++;
}

unsigned int editor_undo_can_undo(void)
{
    return editor_undo_count > 0;
}

void editor_undo(void)
{
    unsigned int row;

    if (editor_undo_count == 0)
        return;

    /*
     * Save the current state into redo history.
     */
    if (editor_redo_count >= EDITOR_REDO_MAX)
    {
        row = 1;

        while (row < EDITOR_REDO_MAX)
        {
            editor_redo_history[row - 1] =
                editor_redo_history[row];

            row++;
        }

        editor_redo_count =
            EDITOR_REDO_MAX - 1;
    }

    row = 0;

    while (row < EDITOR_MAX_LINES)
    {
        editor_redo_history[
            editor_redo_count
        ].lines[row] =
            editor_lines[row];

        row++;
    }

    editor_redo_history[
        editor_redo_count
    ].cursor_row =
        editor_cursor_row;

    editor_redo_history[
        editor_redo_count
    ].cursor_column =
        editor_cursor_column;

    editor_redo_history[
        editor_redo_count
    ].preferred_column =
        editor_preferred_column;

    editor_redo_count++;

    /*
     * Move to the previous undo snapshot.
     */
    editor_undo_count--;

    /*
     * Restore the document.
     */
    row = 0;

    while (row < EDITOR_MAX_LINES)
    {
        editor_lines[row] =
            editor_undo_history[
                editor_undo_count
            ].lines[row];

        row++;
    }

    /*
     * Restore cursor state.
     */
    editor_cursor_row =
        editor_undo_history[
            editor_undo_count
        ].cursor_row;

    editor_cursor_column =
        editor_undo_history[
            editor_undo_count
        ].cursor_column;

    editor_preferred_column =
        editor_undo_history[
            editor_undo_count
        ].preferred_column;
}

unsigned int editor_undo_can_redo(void)
{
    return editor_redo_count > 0;
}

void editor_redo(void)
{
    unsigned int row;

    if (editor_redo_count == 0)
        return;

    /*
     * Save the current state into undo history.
     */
    if (editor_undo_count >= EDITOR_UNDO_MAX)
    {
        row = 1;

        while (row < EDITOR_UNDO_MAX)
        {
            editor_undo_history[row - 1] =
                editor_undo_history[row];

            row++;
        }

        editor_undo_count =
            EDITOR_UNDO_MAX - 1;
    }

    row = 0;

    while (row < EDITOR_MAX_LINES)
    {
        editor_undo_history[
            editor_undo_count
        ].lines[row] =
            editor_lines[row];

        row++;
    }

    editor_undo_history[
        editor_undo_count
    ].cursor_row =
        editor_cursor_row;

    editor_undo_history[
        editor_undo_count
    ].cursor_column =
        editor_cursor_column;

    editor_undo_history[
        editor_undo_count
    ].preferred_column =
        editor_preferred_column;

    editor_undo_count++;

    /*
     * Move to the latest redo snapshot.
     */
    editor_redo_count--;

    /*
     * Restore the redone document state.
     */
    row = 0;

    while (row < EDITOR_MAX_LINES)
    {
        editor_lines[row] =
            editor_redo_history[
                editor_redo_count
            ].lines[row];

        row++;
    }

    /*
     * Restore cursor state.
     */
    editor_cursor_row =
        editor_redo_history[
            editor_redo_count
        ].cursor_row;

    editor_cursor_column =
        editor_redo_history[
            editor_redo_count
        ].cursor_column;

    editor_preferred_column =
        editor_redo_history[
            editor_redo_count
        ].preferred_column;
}
