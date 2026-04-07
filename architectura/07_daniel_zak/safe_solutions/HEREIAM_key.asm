
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h  
l:
mov bx, [1234h]
mov byte [bx], 0cch
   loop l

mov ah, 0
int 16h
ret
