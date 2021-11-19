#ifndef _OYSTER_MEMLAYOUT_H
#define _OYSTER_MEMLAYOUT_H

#include "utils.h"
#include <stdint.h>

#define EXTERM 0x10000000   // start of extended memory
#define PHYSTOP 0xE0000000  // top physical memory
#define DEVSPACE 0xFE000000 // other devices are at high addresses

#define KERNBASE 0x80000000 // first kernel virtual address

// the addr that the kernel linked is linked to
#define KERNLINK (KERNBASE + EXTERM)

MACFN v2p(auto addr) { return static_cast<uint32_t>(addr) - KERNBASE; }
MACFN p2v(auto addr) {
    return static_cast<void *>(static_cast<char *>(addr) + KERNBASE);
}
MACFN v2p_without_cast(auto x) { return x - KERNBASE; }
MACFN p2v_without_cast(auto x) { return x + KERNBASE; }

#endif
