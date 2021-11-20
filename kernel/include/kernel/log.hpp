#ifndef _OYSTER_LOG_H
#define _OYSTER_LOG_H

#include "buffer.hpp"
#include "utils.hpp"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct Logger {
    Logger();

    void write(Buffer *);
    void with_op(auto action) {
        begin_op();
        action();
        end_op();
    }
    void begin_op();
    void end_op();
};

#endif
