// x86 memory management unit

// eflags
#define FL_IF 0x00000200 // enable interrupt

// control register flags
#define CR0_PW 0x00000001 // protection enable
#define CR0_WP 0x00010000 // write protect
#define CR0_PG 0x80000000 // paging

#define CR4_PSE 0x00000010 // page size extension

// segment selectors

#define SEG_K_CODE 1 // kernel code
#define SEG_K_DATA 2 // kernel data and stack
#define SEG_U_CODE 3 // user code
#define SEG_U_DATA 4 // user data and stack
#define SEG_TSS 5    // process's task state

// cpu->gdt[NSEGS]
#define NSEGS 6


// TODO
