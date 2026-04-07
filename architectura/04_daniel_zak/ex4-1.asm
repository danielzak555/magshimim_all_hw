
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h 

jmp main_fun

x dw 0x7F
y dw 0x80

main_fun:
    push x
    push y
       
    call Min
    
    call print_num
    PRINTN
    
    jmp end

PROC Min 
    push bp
    mov bp, sp  
    
    mov bx, [bp + 4]
    mov ax, [bp + 6]
       
    cmp ax, bx 
  
    jb done
    
    mov ax, bx

done: 
    pop bp
    ret 4
ENDP Min 
            

end:
    mov ah, 0
    int 16h
    ret

include magshimim.inc


