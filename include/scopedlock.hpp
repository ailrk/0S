#ifndef _OYSTER_SCOPEDLOCK_H
#define _OYSTER_SCOPEDLOCK_H

#include <utility>

// Lock a block, and release when it's out of scope.

template <typename L> struct ScopedLock {
    L lock;

    ScopedLock(L &&lock)
        : lock(std::move(lock)) {
        lock.acquire();
    }

    ~ScopedLock() { lock.release(); }
};

#endif
