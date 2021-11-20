#ifndef _OYSTER_SPINLOCK_H
#define _OYSTER_SPINLOCK_H

#include "process.hpp"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct SleepLock {
    bool locked;

    uint32_t pid; // pid holding the lock.
    char *name;

    SleepLock(char *);
    SleepLock();
    ~SleepLock();

    void acquire();
    void release();

    int is_holding();

    void pushcli();
    void popcli();
};

#endif
