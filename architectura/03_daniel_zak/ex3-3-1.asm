
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt
org 100h

mov ax, 5
mov cx, ax
dec cx

while:
mul cx
loop while

call print_num
PRINTN
      
mov ah, 0
int 16h
ret

include magshimim.inc


