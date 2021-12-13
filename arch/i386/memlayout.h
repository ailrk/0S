#include <stdint.h>
// memory layout.
#define EXTMEM 0x00100000   // extended mem
#define PHYSTOP 0x0e000000  // top physical mem
#define DEVSPACE 0xfe000000 // devices at high addresses.
#define KERNBASE 0x80000000 // first kernel virtual address

// the addr that the kernel linked is linked to
#define KERNLINK (KERNBASE + EXTERM)

#define V2P(addr) ((unsigned int) (a) - KERNBASE)
#define P2V(addr) ((void *) (((char *) (addr)) + KERNBASE))

#define V2P_WC(addr) ((addr) - KERNBASE)
#define P2V_WC(addr) ((addr) + KERNBASE)
