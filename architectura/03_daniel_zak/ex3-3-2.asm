
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

mov ax, 1010101010101010b
mov bx, ax
mov cx, 16
mov ax, 0;

check:
shr bx, 1
jc is_one
jmp for

is_one:         
inc ax 

for:
loop check



call print_num
PRINTN      
       
mov ah, 0
int 16h
ret

include magshimim.inc