#include "fs.h"

void fs_init(void)
{
}

int fs_open(
    const char *path,
    FSFile *file
)
{
    (void)path;
    (void)file;

    return -1;
}

int fs_read(
    FSFile *file,
    void *buffer,
    unsigned int size,
    unsigned int *bytes_read
)
{
    (void)file;
    (void)buffer;
    (void)size;

    if (bytes_read != 0)
        *bytes_read = 0;

    return -1;
}

int fs_write(
    FSFile *file,
    const void *buffer,
    unsigned int size,
    unsigned int *bytes_written
)
{
    (void)file;
    (void)buffer;
    (void)size;

    if (bytes_written != 0)
        *bytes_written = 0;

    return -1;
}

int fs_close(FSFile *file)
{
    (void)file;

    return -1;
}
