
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h  

error dw "ERROR: division by zero$"

jmp start

hendler:
    push ax
    push dx

    mov dx, offset error
    mov ah, 9h
    int 21h 
    PRINTN

    pop dx
    pop ax

    iret 
    
PROC print_regs
    call print_num_uns 
    PRINTN
    
    mov ax, bx
    call print_num_uns
    PRINTN
    
    mov ax, cx
    call print_num_uns
    PRINTN
    
    mov ax, dx
    call print_num_uns
    PRINTN
    
    mov ax, sp
    call print_num_uns
    PRINTN
    
    mov ax, bp
    call print_num_uns
    PRINTN
    
    mov ax, si
    call print_num_uns
    PRINTN
    
    mov ax, di
    call print_num_uns
    PRINTN
    
    ret
    
ENDP print_regs
               
start: 
    cli  
    
    mov ax, 0
    mov es, ax
    
    mov bx, cs
    mov ax, offset hendler
                                                                                              
    mov word ptr es:[2h], bx  ; by 
    mov word ptr es:[0h], ax 
    
    sti
    
    mov ax, 2h
    xor bx, bx
    pusha 
    
    call print_regs  
    
    popa ; to recover the ax = 2
    pusha
    div bl
    call print_regs 
    popa 


mov ah,0
int 16h
ret

include magshimim.inc              
