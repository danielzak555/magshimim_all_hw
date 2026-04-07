
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

mov ax, 2
mov cl, 13
shl ax, cl
mov ah, 0
int 16h

ret




