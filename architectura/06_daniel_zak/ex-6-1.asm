
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h
           
target_temp db 60           
           
MAIN_TEMP:   
    mov dx, 125  
    in  al, dx
    mov bl,al  

    mov ax,bx
    call print_num_uns

    PRINT ","

    mov al,[target_temp]
    xor ah, ah
    call print_num_uns

    PRINTN ""         

    mov al,bl          
    mov cl,[target_temp]
                
    cmp al,cl
    jl TURN_HEATER_ON

    jge TURN_HEATER_OFF
    
TURN_HEATER_ON:
    mov dx, 127
    mov al, 1
    out dx, al 
    
    mov dx, 125                   ;i know this part is kinda unnesessry but without it the temp  gets to 80  because
                                  ; the printing takes time :)
    in  al, dx          
    mov cl,[target_temp]
                
    cmp al,cl
    jg TURN_HEATER_OFF
     
    jmp check_key
    
TURN_HEATER_OFF:
    mov dx, 127
    mov al, 0
    out dx, al
    
      
    jmp check_key


check_key:
    mov ah,06h
    mov dl,0FFh
    int 21h 

    jz MAIN_TEMP 

    cmp al,'+'
    je inc_target

    cmp al,'-'
    je dec_target

    jmp MAIN_TEMP 


inc_target:
    inc [target_temp]
    jmp MAIN_TEMP

dec_target:
    dec [target_temp]
    jmp MAIN_TEMP


mov ah,0
int 16h
ret

include magshimim.inc