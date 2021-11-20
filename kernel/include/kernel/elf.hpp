#ifndef _OYSTER_SYSCALL_TTY_H
#define _OYSTER_SYSCALL_TTY_H

// ELF executable format

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// file header

struct ElfHeader {
    uint32_t magic;
    unsigned char elf[12];
    uint16_t type;
    uint16_t machine;

    uint32_t version;
    uint32_t entry;
    uint32_t phoff;
    uint32_t shoff;
    uint32_t flags;
    uint32_t ehsize;
    uint32_t phentsize;
    uint32_t phnum;
    uint32_t shentsize;
    uint32_t shnum;
    uint32_t shstrndx;
};

// program section header
struct ProgHeader {
    uint32_t type;
    uint32_t off;
    uint32_t vadr;
    uint32_t paddr;
    uint32_t filesz;
    uint32_t memsz;
    uint32_t flags;
    uint32_t align;
};

#define ELF_PROG_LOAD 1

#define ELF_PROG_FLAG_EXEC 1
#define ELF_PROG_FLAG_WRITE (1 << 1)
#define ELF_PROG_FLAG_READ (1 << 2)

#endif
