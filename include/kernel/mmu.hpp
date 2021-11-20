// memory management unit.

#ifndef _OYSTER_MEMLAYOUT_H
#define _OYSTER_MEMLAYOUT_H

#include "utils.h"
#include <stdint.h>

// Eflags
#define FL_IF 0x00000200 // interrupt enable

// control register flags
#define CR0_PE 0x00000001 // protection enable
#define CR0_WP 0x00010000 // write protect
#define CR2_PG 0x00010000 // paging

// segment selector
#define SEG_KCODE 1 // kernel code
#define SEG_KDATA 2 // kernel data + stack
#define SEG_UCODE 3 // user code
#define SEG_UDATA 4 // user data + stack
#define SEG_TSS 5   // current process's task state

// cpu->gdt[NSEGS] holds segment above
#define NSEGS 6

// segment descriptor
struct SegmentDescriptor {
    unsigned int limit_15_0 : 16;     // low bits of segment limit
    unsigned int base_15_0 : 16;      // low bits of segment base address
    unsigned int base_32_16 : 8;      // middle bits of segment base address
    unsigned int type : 4;            // segment type (STS_)
    unsigned int s : 1;               // 0 = system, 1 = application
    unsigned int privilege_level : 2; // descriptor privilegelevel
    unsigned int present : 1;         // present
    unsigned int limit_19_16 : 4;     // high bits of sement limit
    unsigned int avl : 1;             // available for software use (unused.)
    unsigned int reserved : 1;
    unsigned int db : 1;           // 0 = 16 bit segment, 1 = 32 bit segment.
    unsigned int gruanilarity : 1; // limit scaled by 4k when set.
    unsigned int base_31_24 : 8;   // high bits of sement base address.
};

// system segment type bits
#define STS_T32A 0x9 // avilable 32 bit TSS
#define STS_IG32 0xE // 32 bit interrupt gate
#define STS_TG32 0xF // 32 bit trap gate

// task state segment format.
struct TaskState {
    uint32_t link;
    uint32_t esp0; // sp and segment selectors

    uint16_t ss0; // after an increase in privilege level.
    uint16_t padding0_;

    uint32_t *esp1;
    uint32_t *ss1;

    uint16_t padding1_;

    uint32_t *esp2;
    uint32_t *ss2;

    uint16_t padding2_;

    void *cr3;     // page dir base
    uint32_t *eip; // saved state from last task switch

    uint32_t eflags;

    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t *esp;
    uint32_t *ebp;
    uint32_t esi;
    uint32_t edi;
    uint32_t es;

    uint16_t padding3_;
    uint16_t cs;

    uint16_t padding4_;
    uint16_t ss;

    uint16_t padding5_;
    uint16_t ds;

    uint16_t padding6_;
    uint16_t fs;

    uint16_t padding7_;
    uint16_t gs;

    uint16_t padding8_;
    uint16_t ldt;

    uint16_t padding9_;
    uint16_t trap;

    uint16_t padding10_;
    uint16_t io_map_baseaddr;
} __attribute__((packed));

struct GateDescriptor {
    uint32_t off_15_0 : 16;     // low 16 bit of offset in segment
    uint32_t code_segment : 16; // code segment selector
    uint32_t args : 5;          // # args. 0 for interrupt / trap gates.
    uint32_t reserved : 3;
    uint32_t type : 4;            // STS_{IT32, TG32}
    uint32_t s : 1;               // must be 0 (system).
    uint32_t privilege_level : 2; // descriptor privilege_level
    uint32_t present : 1;         // descriptor privilege_level
    uint32_t off_31_16 : 16;      // high bits of offset in segment

    void setup(bool istrap, auto sel, auto off, auto d) {
        this->off_15_0 = (uint32_t)(off)&0xffff;
        this->code_segment = sel;
        this->args = 0;
        this->reserved = 0;
        this->type = istrap ? STS_TG32 : STS_IG32;
        this->s = 0;
        this->privilege_level = d;
        this->present = 1;
        this->off_31_16 = (uint32_t)(off) >> 16;
    }
};

// TODO

#endif
