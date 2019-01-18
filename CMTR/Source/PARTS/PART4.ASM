;czesc czwarta

mov eax,tex3
call initbitmap
mov counter,0

pp4:
mov ax,offset kula
call generuj
call drawbitmap
mov al,x1adder
mov ah,al
push ax
shl eax,16
pop ax
;mov fontcol,eax
mov fontcol,0
call render
call drop

mov ax,counter
cmp ax,4*60
jl pp4
