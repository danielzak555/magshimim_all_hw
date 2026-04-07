
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

s:
mov word [0A2h], 0x0
mov dx, 18 ; amit i had to make an instruction to waste time, sorry :(
mov bx, 0x0
sub bx, [0A2h]
mov [0A2h],bx
jmp s

mov ah, 0
int 16h
ret