#pragma once
#include "../ostl/utility.hpp"

// Lock a block, and release when it's out of scope.

template <typename L> struct ScopedLock {
    L lock;

    ScopedLock(L &&lock)
        : lock(ostl::move(lock)) {
        lock.acquire();
    }

    ~ScopedLock() { lock.release(); }
};
