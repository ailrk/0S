    ;; the loader file will place boot.s at 0x80000000, and qemu -kernel
    ;; loads the kernel at 0x80000000.
    ;; all cpu will jump to the same location at the beginning and run
    ;; boot.s
.section .text
.global boot
boot:
    la sp, kernel_stack_top
    li a0, 1024*4
    csrr a1, mhartid
    addi a1, a1, 1
    mul a0, a0, a1
    add sp, sp, a0
    call kmain

    ;; once start is finished keep spinning.
spin:
    j spin
