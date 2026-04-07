org 100h
mov bx, 1805h
mov [1980h], bx

l:
    loop l
mov ah, 0
int 16h
ret