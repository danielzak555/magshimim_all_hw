
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

loop:
    mov bx, 0010h
write:
    mov word [bx], 00cch
    add bh, 1
    cmp bh, 17
    jb write

    jmp loop

mov ah, 0
int 16h
ret