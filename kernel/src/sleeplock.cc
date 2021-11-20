#include "../include/kernel/sleeplock.hpp"
#include "../include/kernel/memlayout.hpp"
#include "../include/kernel/process.hpp"

SleepLock::SleepLock(char *name)
    : name(name)
    , locked(false)
    , pid(0) // TODO  once sleep lock is spawned pid should be the current pid

{}
