#ifndef _OYSTER_SPINLOCK_H
#define _OYSTER_SPINLOCK_H

// spin lock implementation.
// SpinLock doesn't trigger context switch, and it's based on
// busy waiting.

#include "process.hpp"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct SpinLock {
    bool locked;

    // lock name
    char *name;

    CPU *cpu; //  the cpu holding the lock.

    // call stack  as an array of program counters that locked
    // the lock
    uint32_t pcs[10];

    SpinLock(char *);
    SpinLock();
    ~SpinLock();
    void acquire();
    void release();
    void get_caller_pcs(void *v, uint32_t pcs[]);
    int is_holding();

    void pushcli();
    void popcli();
    void withcli(auto cb);
};

#endif
