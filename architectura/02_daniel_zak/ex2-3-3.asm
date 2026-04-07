
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

;mul by 32         
shl bx, 5

;mul by 41
mov ax, bx
shl bx, 5
mov cx, bx
shr dx, 2
add bx, ax
add bx, cx
mov ah, 0
int 16h


ret




