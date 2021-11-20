#include "../include/kernel/buffer.hpp"
#include "../include/kernel/fs.hpp"
#include "../include/kernel/log.hpp"
#include "../include/kernel/param.hpp"
#include "../include/kernel/sleeplock.hpp"
#include "../include/kernel/spinlock.hpp"

// logging with concurrent fs system calls.

struct LogHeader {
    int n;
    int block[config::LOG_SIZE];
};
