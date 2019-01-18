;czesc czwarta

mov eax,tex3
call initbitmap
mov counter,0

pp4:
mov ax,offset kula
call generuj
call drawbitmap
;mov al,x1adder
;mov ah,al
;push ax
;shl eax,16
;pop ax
;mov fontcol,eax
mov fontcol,0
call render
call drop

mov ax,counter
cmp ax,4*60
;cmp ax,10
jl pp4




;napis koncowy
mov byte ptr[flashdir],1
mov ax,0ffh
mov byte ptr flashcol,al
xor bx,bx
call makefontcolor
mov esi,endtxt
;mov edi,bufor+320*4*(100-16)+40*4
xor eax,eax
mov edi,bufor
mov cx,320*4*(100-16)/4+320
l1p:
mov [edi],eax
add edi,4
dec cx
jnz l1p

;drukuj napis
mov edi,bufor+320*4*(100-16)+40*4
mov cx,320*32
eloop:
cmp byte ptr[esi],0
jne nextel
mov dword ptr[edi],0
nextel:
add esi,1
add edi,4
dec cx
jnz eloop

xor eax,eax
mov edi,bufor+320*4*(100-16+32)
mov cx,320*4*(100-16)/4+320
l2p:
mov [edi],eax
add edi,4
dec cx
jnz l2p


call drop


mov counter,0
waitend:
mov ax,counter
cmp ax,60
jb waitend
