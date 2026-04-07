
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

mov ax, 1f4h
add ax, 1011b
mov dx, ax
mov ah, 0
int 16h

ret




