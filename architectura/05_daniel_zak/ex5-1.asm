
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

push a
push b
push c
call mystery
add sp, 6
jmp end


mystery PROC
    push    bp
    mov     bp, sp
    mov     ax, [bp+6]
    imul    ax
    mov     dx, ax
    mov     ax, [bp+4]
    shl     ax, 2
    imul    [bp+8]
    sub     dx, ax
    mov     ax, dx
    pop     bp
    ret
ENDP

end:


mov ah, 0
int 16h
ret