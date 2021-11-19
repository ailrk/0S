#ifndef _OYSTER_PROCESS_H
#define _OYSTER_PROCESS_H

#include "utils.h"
#include <stdint.h>

// cpu state
struct CPU {
    unsigned char apicid; // local apic id.
    // TODO
};

#define NCPU 4

using CPUS = CPU[NCPU];

CPUS cpus;
uint32_t ncpu;

//
// context
//

struct Context {
    uint32_t edi;
    uint32_t esi;
    uint32_t ebx;
    uint32_t ebp;
    uint32_t eip;
};

enum ProcessState {
    UNUSED,
    EMBRYO,
    SLEEPING,
    RUNNABLE,
    RUNNING,
    ZOMBIE
};

struct Process {
    uint32_t memory_size;
    pageTable *pgdir;
    // TODO


};

#endif
