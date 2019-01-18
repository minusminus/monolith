;czesc druga

mov eax,tex2
call initbitmap
mov byte ptr[flashdir],0
mov edi,bufor+320*4*32
mov esi,gp1
mov bx,0
mov fontflash,0ffh

pp3m:
push bx
mov counter,0
;mov fontflash,0ffh

pp3:
push esi edi

mov ax,offset greetsy
call generuj
call drawbitmap
;mov dword ptr[fontcol],0
;call render

mov ax,fontflash
mov byte ptr flashcol,al

xor bx,bx
call makefontcolor

pop edi esi
push esi edi
call printfonttbl
call drop

pop edi esi
mov ax,counter
cmp ax,70
;cmp ax,30
jb pp3

pop bx
xor byte ptr[flashdir],-1
add edi,320*4*26/2+160*4
add esi,c2-c1
inc bx
cmp bx,8
jb pp3m
