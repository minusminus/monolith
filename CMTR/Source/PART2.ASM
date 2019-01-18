;czesc druga

mov eax,tex1
call initbitmap
mov byte ptr[flashdir],0
mov edi,bufor+320*4*10
mov esi,c1
mov bx,0

pp2m:
push bx
mov counter,0
mov fontflash,0ffh

pp2:
push esi edi

mov ax,offset kula
call generuj
call drawbitmap
mov dword ptr[fontcol],0
call render

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
cmp ax,2*60
;cmp ax,30
jb pp2

pop bx
add edi,320*4*40
add esi,c2-c1
inc bx
cmp bx,5
jb pp2m
