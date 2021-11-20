#ifndef _OYSTER_FS_H
#define _OYSTER_FS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "utils.hpp"


// file system format.

#define ROOTNO 1    // root i number
#define BLOCKSZ 512 // block size

// Disk Layout:
// [ boot block | super block | log | inode blocks | free bit map | data blocks]

struct SuperBlock {
    uint32_t size;
    uint32_t nblocks;
    uint32_t nindoes;
    uint32_t nlog;
    uint32_t logstart;
    uint32_t inodestart;
    uint32_t bmapstart;
};

#define NDIRECT 12
#define NINDIRECT (BSIZE / sizeof(uint32_t))
#define MAXFILE (NDIRECT + NINDIRECT)

struct DInode;

struct DInode {
    uint16_t type;               // file type
    uint16_t major;              // major device number
    uint16_t minor;              // minor device number
    uint16_t nlink;              // # of links to inode in fs
    uint32_t size;               // size of file in bytes
    uint32_t addrs[NDIRECT + 1]; // data block addresses
} __pack;

MACFN inode_per_block() { return BLOCKSZ / sizeof(DInode); }
MACFN block_with_incode(auto i, SuperBlock sb) {
    return (i) / inode_per_block() + sb.inodestart;
}
MACFN bitmap_bits_per_block() { return BLOCKSZ * 8; }
MACFN block_with_bit(auto b, SuperBlock sb) {
    return b / bitmap_bits_per_block() + sb.bmapstart;
}

// a directory is a file contains a list of Dirent
#define DIRSIZE 14

struct Dirent {
    uint16_t inum;
    char name [DIRSIZE];
};

#endif
