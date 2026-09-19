#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

#include <stdint.h>

typedef struct
{
    uint64_t base;
    uint64_t length;
    uint32_t type;
    uint32_t attributes;
} memory_region_t;

#endif
