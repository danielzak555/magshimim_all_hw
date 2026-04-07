
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt 

org 100h

table dw case1, case2, case3, case4
theNum dw 2
       
       
start:
mov si, [theNum]
mov bx, si
mov bx, [table + bx]
jmp bx       
       
case1:
PRINTN "Number One"
jmp end

case2:
PRINTN "Number Two"
jmp end

case3:
PRINTN "Number Three"
jmp end

case4:
PRINTN "Number Four"
jmp end

end: 
             
mov ah, 0
int 16h
ret

include magshimim.inc



