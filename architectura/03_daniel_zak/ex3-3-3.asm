
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt 

org 100h

array db 1, 99 dup(0)
row db 0
col db 0
size db 10
first db 0
second db 0
final db 0
sum dw 0

mov cx, 100


start:
mov al, [col]
mov bx, 0
cmp ax, bx
je is_first_col


mov al, [row]
mov bx, 0
cmp ax, bx
je is_first_row


mov si, 0
mov al, [row]
mov bl, 10
mul bl
add si, ax

sub si, 10
mov dl, [col]
mov dh, 0
add si, dx

mov al, [array + si] 
mov second, al 

dec si
mov al, [array + si] 
mov first, al

mov al, [first]
add al, [second]
mov final, al

mov al, [row]
mov bl, [size]
mul bl
add al, [col]
mov si, ax

mov al, [final]
mov [array + si], al

point:

mov al, [col]
inc al
mov bl, 10
cmp al, bl
je last_col
mov col, al

point3:

loop start

mov cx, 10
jmp sum_calc

   

is_first_col:
mov al, [row]
mov bl, [size]
mul bl
mov ah, 0
mov si, ax
mov ax, 1
mov [array + si], al
mov al, 0
mov al, [array + si]
mov final, al
jmp point

is_first_row:
add al, [col]
mov ah, 0
mov si, ax
mov al, 0
mov [array + si], al
mov al, 0
mov al, [array + si]
mov final, al
jmp point


last_col:
mov col, 0
mov al, [row]
inc al
mov row, al
jmp point3
 
 

sum_calc: 
mov al, cl
add al, 90
dec al
mov ah, 0
mov si, ax
mov al, [array + si]
add sum, ax
loop sum_calc

end: 
mov ax, [sum]
call print_num
PRINTN 
         
       
mov ah, 0
int 16h
ret

include magshimim.inc



