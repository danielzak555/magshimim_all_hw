
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

mov al, 0f2h 
mov bl, al
mov bh, 0
mov ah, 0
int 16h

ret




