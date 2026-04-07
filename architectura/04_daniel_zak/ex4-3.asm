
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

jmp main_fun

arr dw 8, 3, 3, 19, 2, 1
size dw 6


main_fun:
    push offset arr
    push size
    call SortArray

    PRINTN "sorted:"
    mov cx, size
    mov di, offset arr

print_loop:
    mov ax, [di]
    call print_num
    PRINT " "
    add di, 2
    loop print_loop

    jmp end



PROC SortArray
    push bp
    mov bp, sp
    sub sp, 4   ;[bp-2] = min_index, [bp-4] = i     i messed up with it at the start so iwrote so you wount mess up 

    mov ax, 0
    mov [bp-4], ax  

sort_outer:
    mov ax, [bp-4]
    cmp ax, [bp+4]  
    jge sort_done

    push ax       ; i
    push [bp+4]   ; size
    push [bp+6]   ; arr
    call FindMin  ; ax = min_index

    mov [bp-2], ax  ; store min_index
                                            

    mov bx, [bp+6]      ; arr base
    mov ax, [bp-4]      ; i
    shl ax, 1           ; alon i think shl is  kinda better then mul so i hope you understand
    add bx, ax          ; pointer to arr[i]

    mov si, [bp+6]
    mov ax, [bp-2]
    shl ax, 1
    add si, ax          ; pointer to arr[min]

    
    push si     ; pointer to arr[min]
    push bx     ; pointer to arr[i]
    call Swap

    mov ax, [bp-4]
    inc ax
    mov [bp-4], ax
    jmp sort_outer

sort_done:
    mov sp, bp
    pop bp
    ret 4
ENDP SortArray





PROC FindMin
    push bp
    mov bp, sp
    sub sp, 2 

    mov bx, [bp+8]   ; start index
    mov [bp-2], bx   ; min_index = start

    mov di, [bp+4]   ; arr
    mov ax, [bp+8] 
    shl ax, 1
    add di, ax    

    mov dx, [di]     ; current min value in DX

find_loop:
    mov ax, [bp+8]
    inc ax
    mov [bp+8], ax  

    cmp ax, [bp+6]
    jge find_done  

    mov di, [bp+4]
    mov bx, [bp+8]
    shl bx, 1
    add di, bx
    mov ax, [di]      

    cmp ax, dx
    jae skip_update

    mov dx, ax           ; new minimum value
    mov bx, [bp+8]       ; new min index
    mov [bp-2], bx

skip_update:
    jmp find_loop

find_done:
    mov ax, [bp-2]       ; return index

    mov sp, bp
    pop bp
    ret 6
ENDP FindMin



PROC Swap
    push bp
    mov bp, sp 
    sub sp, 2
    
    mov si, [bp + 4]   ; pointer to arr[i]
    mov di, [bp + 6]   ; pointer to arr[min]
    
    mov ax, [di]
    mov [bp - 2], ax  
    mov ax, [si]
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
