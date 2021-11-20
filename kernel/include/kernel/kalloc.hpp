#ifndef _OYSTER_KALLOC_H
#define _OYSTER_KALLOC_H

#include "memlayout.hpp"
#include "spinlock.hpp"

// phys mmeory allocator. allocates 3096 byte pages.

char *kalloc();
void kfree(char *);
void kinit1(void *, void *);
void kinit2(void *, void *);

void freerange(void *vstart, void *vend);

// first address afte kernel loaded from ELF file.
// defined by the kernel linker script in kernel.ld
extern char end[];

struct Run {
    Run *next;
};

struct KMem {
    SpinLock lock;
    bool use_lock;
    Run *freelist;
};

KMem kmem;

// init process:
// step 1. main() calls kinit1() with entrypgdir
// step 2. main() calls kinit2() with the rest of the phys pages

void kinit1(void *vstart, void *vend) {
    SpinLock();
    kmem.use_lock = false;
    freerange(vstart, vend);
}

void kinit2(void *vstart, void *vend) {
    freerange(vstart, vend);
    kmem.use_lock = true;
}

#endif
