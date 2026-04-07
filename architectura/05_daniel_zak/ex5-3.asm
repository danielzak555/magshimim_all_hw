
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

jmp main_fun

P dw 7
Q dw 19 
totient dw 0
pub_key dw 29  ; i did the exact nums in the video      
private_key dw 0

main_fun:
    push [Q]
    push [P]
    call calc_tot
    mov [totient], ax 
    
    mov ax, [totient]
    call print_num     ; i did it just to know the tot is ok it shouldent bother you
    PRINTN       
    
    
    call is_valid_pub_key
    cmp ax, 0
    je end

    push [pub_key]
    call calc_private_key
    mov [private_key], bx

    mov ax, [private_key]
    call print_num 
    PRINTN

    jmp end

PROC calc_tot
    push bp
    mov bp, sp 
    
    mov ax, [bp + 4] 
    mov bx, [bp + 6] 
    
    dec ax          
    dec bx 
    
    mul bx    
    
    mov sp, bp
    pop bp
    ret 4 
ENDP calc_tot
                                       
                                       

PROC is_valid_pub_key
    push bp
    mov bp, sp
    
    mov ax, [pub_key]
    cmp ax, [totient]
    jge key_invalid
    
    push [pub_key]
    call is_prime
    cmp ax, 0
    je key_invalid 
    
    push [totient]  ; the num first then divisorr im not dumn haahahaa ,,,,,,,,,,,, i know you smilled 
    push [pub_key] 
    call modolu_oper
    cmp ax, 0
    je key_invalid
                  
    mov ax, 1
    jmp key_valid_end
    
                  
key_invalid:
    mov ax, 0

key_valid_end:
    pop bp
    ret
ENDP is_valid_pub_key
            
                                              

PROC calc_private_key
    push bp
    mov bp, sp
    
    mov cx, [bp + 4]
    mov bx, 1    
    
search_loop:
    inc bx    
    
    cmp bx, [totient]
    jg not_found
    
    mov ax, bx 
    mul cx  
    
    div [totient]
    
    cmp dx, 1           ; i assked ai how to find the reminder easiealy and he said it stored in dx so its nice tks :)
    je found_private
    
    jmp search_loop

found_private:
    pop bp
    ret 2

not_found:
    mov bx, 0      
    pop bp
    ret 2
ENDP calc_private_key 
   
   
   
PROC modolu_oper
    push bp
    mov bp, sp 
    
    push bx
    push dx

    mov ax, [bp + 6]    ;num
    mov bx, [bp + 4]    ;divisor
    
    xor dx, dx
    
    cmp bx, 0
    je error_div_by_zero
    
    div bx  
    
    mov ax, dx 

    jmp modo_end

error_div_by_zero:
    PRINTN "cant div by zero"
    jmp end

modo_end:
    pop dx
    pop bx
    
    pop bp
    ret 4  
ENDP modolu_oper                            


PROC is_prime
    push bp
    mov bp, sp
    
    push bx     ; idont wanna loss them :(
    push cx
    push dx
    
    mov ax, [bp + 4]    ; num
    
    cmp ax, 2           
    jl not_prime_case
    cmp ax, 2          
    je prime_case
    
    xor dx, dx       
    mov bx, 2        
    div bx         ; to check the even nums :) i know math
    cmp dx, 0
    je not_prime_case
    
    mov cx, 3        
    mov bx, [bp + 4]
    shr bx, 1           ; bx is half of the num so it finishes faster, and again you see i know mathmatics, its like first class or soo
    
check_loop:
    cmp cx, bx      
    jg prime_case 
    
    mov ax, [bp + 4]   
    mov dx, 0           
    div cx           
    
    cmp dx, 0
    je not_prime_case
    
    add cx, 2       ; to not check the even jjust odd
    jmp check_loop

not_prime_case:
    mov ax, 0
    jmp prime_end

prime_case:
    mov ax, 1

prime_end:
    pop dx
    pop cx
    pop bx
    
    pop bp
    ret 2    
ENDP is_prime

end:
    mov ah, 0
    int 16h
    ret

include magshimim.inc

