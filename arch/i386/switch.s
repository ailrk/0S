# context switch
# void switch(Context **old, Context *new);


.global switch

switch:
    mov eax, [esp+4]
    mov edx, [esp+8]

    # callee saved registers
    push ebp
    push ebx
    push esi
    push edi

    # switch stacks
    mov eax, esp
    mov dsp, edx

    # load callee saved registers
    pop ebp
    pop ebx
    pop esi
    pop edi
    ret
