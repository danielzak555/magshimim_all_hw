
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h 

jmp main_fun

x dw 0x7F
y dw 0x80

main_fun:
    push offset x
    push offset y
    
    PRINTN "before the swap"
    mov ax, x
    call print_num
    PRINT ", " 
    mov ax, y
    call print_num
    PRINTN
    
       
    call Swap  
    
    
    PRINTN "after the swap"
    mov ax, x
    call print_num
    PRINT ", " 
    mov ax, y
    call print_num
    PRINTN
    
    jmp end

PROC Swap
    push bp
    mov bp, sp 
    sub sp, 2
    
    mov si, [bp + 4] ; y
    mov di, [bp + 6] ; x
    
    mov ax, [di] ; x
    mov [bp - 2], ax  
    mov ax, [si] ; y
    mov [di], ax
    mov ax, [bp - 2]
    mov [si], ax
 
    mov sp, bp   
    pop bp
    ret 4
ENDP Swap 
            

end:
    mov ah, 0
    int 16h
    ret

include magshimim.inc
