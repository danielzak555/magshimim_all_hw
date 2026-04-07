org  100h

jmp start

; [belongs to (A)]
num1    dw 7
num2    dw 3
num3    dw 2

; [belongs to (B)]
chrs    db  'A','B','C','D'
chrs_ptr    dw  offset chrs

; [belongs to (D)] - for the "static" part, change only these two lines
static_num1_ptr    dw  offset num1;
static_num1_ptr_ptr    dw  offset static_num1_ptr;

; [belongs to (E)] - for the "dynamic" part, do NOT use the "offset"
; keyword and do NOT change the next two lines
dynamic_num1_ptr   dw 0;
dynamic_num1_ptr_ptr dw 0;

start:

 ; PART (A)
; Print 23. Use num1, num2, num3 exactly once.
; Do not use immediates!
        PRINTN   "Part (A) - should print 23"
; Write your code here
        mov ax, num1
        add ax, num1
        add ax, num2
        add ax, num2
        add ax, num2
        call print_num
        PRINTN


; PART (B)
; Print 'C'. Do not use 'chrs' but only 'chrs_ptr'
        PRINTN   "Part (B) - should print C"
        mov bx, chrs_ptr
        add bx, 2
        mov al, [bx]
        call print_al_chr
        PRINTN

; PART (C)
; Print '15', using ONLY 'mov' and 'lea'.
; Do NOT use arithmetic instrutions (add, inc, mul, etc.)
        PRINTN   "Part (C) - should print 15"
        mov ax, 10
        mov bx, 4
        mov si, ax 
        lea bx, [bx + si + 1]
        mov ax, bx

		call print_num
        PRINTN

; PART (D)
; Make the "static" code print 7 by only changing the above two
; definitions. Do NOT add/change the next 5 lines
        PRINTN   "Part (D) - should print 7"
        mov bx,static_num1_ptr_ptr
        mov bx,[bx]
        mov ax,[bx]
        call print_num
        PRINTN


; PART (E)
; Make the "dynamic" code print 7 without using the "offset" keyword.
; Write your code here
        PRINTN   "Part (E) - should print 7"
        lea bx, num1 
        mov dynamic_num1_ptr, bx
        lea bx, dynamic_num1_ptr  
        mov dynamic_num1_ptr_ptr, bx
; Do not change the next 4 lines
        mov bx,dynamic_num1_ptr_ptr
        mov bx,[bx]
        mov ax,[bx]
        call print_num
        PRINTN
        mov ah, 0
        int 16h
		ret

include magshimim.inc
