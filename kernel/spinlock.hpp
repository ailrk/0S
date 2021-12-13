#pragma once
// spin lock implementation.
// SpinLock doesn't trigger context switch, and it's based on
// busy waiting.

#include "proc.hpp"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct SpinLock {
    bool locked;
    char *name; // lock name
    CPU *cpu;   //  the cpu holding the lock.
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
