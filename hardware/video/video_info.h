#ifndef VIDEO_INFO_H
#define VIDEO_INFO_H

#include <stdint.h>

#define VIDEO_INFO_ADDRESS 0x9000

typedef struct
{
    uint16_t pitch;
    uint16_t width;
    uint16_t height;
    uint8_t  bpp;
    uint32_t framebuffer;
} video_info_t;

#endif
