// put the content of crtend.o to the corresponding init
// or fini section

.section .init
    popl %ebp
    ret

.section .fini
    popl %ebp
    ret
