#ifndef FS_H
#define FS_H

#define FS_READ   0x01
#define FS_WRITE  0x02

#define FS_SUCCESS       0
#define FS_ERROR        -1
#define FS_NOT_FOUND     -2
#define FS_INVALID       -3
#define FS_NO_SPACE      -4
#define FS_IO_ERROR      -5

typedef struct
{
    unsigned int size;
    unsigned int position;
    unsigned int flags;
} FSFile;

void fs_init(void);

int fs_open(
    const char *path,
    FSFile *file
);

int fs_read(
    FSFile *file,
    void *buffer,
    unsigned int size,
    unsigned int *bytes_read
);

int fs_write(
    FSFile *file,
    const void *buffer,
    unsigned int size,
    unsigned int *bytes_written
);

int fs_close(FSFile *file);

#endif
