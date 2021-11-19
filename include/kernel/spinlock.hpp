#ifndef _OYSTER_SPINLOCK_H
#define _OYSTER_SPINLOCK_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct SpinLock {
    bool locked;


    // lock name
    char *debug_name;

    // call stack  as an array of program counters that locked
    // the lock
    uint32_t pcs[10];
};

#endif
