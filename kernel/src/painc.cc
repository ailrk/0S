#include "../include/kernel/console.hpp"

Console Console::init() {}

void Console::panic(char *) {
    int i;
    uint32_t pcs[10];

    cprintf("lacpicid %d: painc: ", lapicid());
}
void Console::cprintf(char *msg, ...) {}
