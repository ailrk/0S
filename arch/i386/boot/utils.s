;; utils for intel i386 bootloader.

bits 16

;;;; basic string display
; print a new line
newline_16:
    mov ah, 0x0e                ; bios call # 0x0e, display char
    mov al, 0x0a                ; display 0x0a '\n'
    int 0x10

    mov al, 0x0d                ; display 0x0d
    int 0x10
    ret

; si points to a null terminated string
println_16:
    mov ah, 0x0e                ; bios call # 0x0e, display char
    .loop
        lodsb
        test al, al             ; null terminated
        je .end
        int 0x10
        jmp .loop
    .end
        call newline_16
        ret

print_16:
    mov ah, 0x0e
    .loop
        lodsb
        test al, al
        je .end
        int 0x10
        jmp .loop
    .end
        ret


;;;; Wait for keypress
; Using port IO with ps/2 controller.
; ps/2  has two one byte buffers: one byte for received and one byte for send.
; https://wiki.osdev.org/%228042%22_PS/2_Controller
; 0x60: r/w  data port
; 0x64: r  status reg
;               0 output buffer status  (keyboard's perspective)
;               1 input buffer status
;               ...
; 0x64: w  command reg

#ifdef INTERRUPT_ENABLED
wait_key:
    jmp wait_key_interrupt:
    ret
#else
wait_key:
    jmp wait_key_polling
    ret
#endif


wait_key_polling:

    mov al, 0xd2                ; write the next byte to input buffer
    out 0x64, al

    ; 0x80 is not a valid key. if the buffer is 0x80 means no key entered.
    mov al, 0x80                ; write 0x80 (126 ascii) to the buffer
    out 0x60, al

    .wait
        in al, 0x60             ; load keyboar data status
        test al, 0x2            ; check input buffer status.
    jnz .wait

    .keydown:
        in al 0x60              ; key is pressed

    ret
