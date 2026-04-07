push ax
xor ax, ax
mov al, 34h
rol al, 1
mov bl, 1
shl bl, 2
inc bl
mul bl
push ax
mov dl, bl
xor dh, dh
add dx, 7D9h
sub dx, 7CFh
sub dx, 0Ah
pop ax
imul dx
sub ax, 795
mov bx, ax
pop ax  
loc_0:  
    mov     ax, bx
    cmp     ds:1980h, ax
    jnz     loc_0  
