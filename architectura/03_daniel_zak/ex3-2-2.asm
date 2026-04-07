
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h
mov al, 0x80
mov ah, 0x7F
cmp ah, al
jg ah_is_bigger_sin
jl ah_is_smaller_sin
je equal_sin

next:
mov al, 0x80
mov ah, 0x7F
cmp ah, al
ja ah_is_bigger_uns
jb ah_is_smaller_uns
je equal_uns
          
ah_is_bigger_uns:
PRINTN "Unsigned comparison: AH is bigger"
jmp next2

ah_is_smaller_uns:
PRINTN "Unsigned comparison: AH is smaller" 
jmp next2

equal_uns:
PRINTN "Unsigned comparison: AH equal to AL"
jmp next2

ah_is_bigger_sin:
PRINTN "Signed comparison: AH is bigger"
jmp next

ah_is_smaller_sin:
PRINTN "Signed comparison: AH is smaller"
jmp next

equal_sin:
PRINTN "Signed comparison: AH equal to AL"
jmp next


next2:          
       
mov ah, 0
int 16h
ret

include magshimim.inc



ret




