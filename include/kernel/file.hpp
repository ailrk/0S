#ifndef _OYSTER_FILE_TTY_H
#define _OYSTER_FILE_TTY_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct File {
    enum { FD_NONE, FD_PIPE, FD_INODE } type;
    int reference_count;
    bool readable;
    bool writable;

};

#endif
