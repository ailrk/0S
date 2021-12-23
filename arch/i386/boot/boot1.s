;; boot loader stage 1
;; 1. enter real mode
;; 2. setup A20 bit
;; 3. read extra memory
;; 4. go to boot loader stage 2.

#include "utils.s"

section .boot
    bits 16
    global boot


;;;; real mode boot
boot:
    call clear_screen
    call hide_cursor
    call enable_a20

    mov si, greeting_msg            ; greeting
    call println_16

;;;; procesures

clear_screen:
    mov ah, 0x06
    xor al, al
    xor bx, bx
    mov bh, 0x07
    xor cx, cx
    mov dh, 0x18
    mov dl, 0x4f
    int 0x10
    ret

enable_a20:
    mov ax, 0x2401
    int 0x15
    ret

hide_cursor:
    ; hide cursor
    mov ah, 0x01
    mov cx, 0x2607
    int 0x10

    ; move cursor to top left position
    mov ah, 0x02
    xor bx, bx,
    xor dx, dx
    int 0x10
    ret

;;;; error handling



load_error:
    mov si, load_failed_msg
    call println_16
    jmp $                      ; loop if error happened.

;;;; messages

greeting_msg db "[Ok] Booting AOS", 0
load_failed_msg db "[Err] "
