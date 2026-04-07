
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h
l:        
mov word [00DEDh], 0h          
mov bx, [00DEDh]
mov word [bx], 0cch 
loop l

mov ah, 0
int 16h
ret