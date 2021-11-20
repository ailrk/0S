#ifndef _OYSTER_BUFFER_H
#define _OYSTER_BUFFER_H

#include "blosc.h"
#include "fs.hpp"
#include "sleeplock.hpp"
#include "utils.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct Buffer {
    int flags;
    uint32_t dev;
    uint32_t blockno;
    SleepLock lock;
    uint32_t reference_count;

    // LRU cache list;
    Buffer *prev;
    Buffer *nextx;

    // disk queue
    Buffer *qnest;

    unsigned char data[BLOCKSZ];
};

#define B_VALID 0x2
#define B_DIRTY 0x4

#endif
