#ifndef _OYSTER_CONSOLE_H
#define _OYSTER_CONSOLE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>



struct Console {
    Console() = delete;
    Console(Console const &) = delete;
    Console(Console &&) = delete;

    static int painicked;

    static Console init();

    void panic(char *) __attribute__((noreturn));
    void cprintf(char *, ...);
};

int Console::painicked = 0;

#endif
