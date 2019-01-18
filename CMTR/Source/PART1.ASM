;poczatkowy tunel
;extrn bumpytunel:near
mov counter,0
mov fontflash,0
mov byte ptr[flashdir],1

pp1:
call bumpytunel

mov ax,fontflash
mov byte ptr flashcol,al

xor bx,bx
call makefontcolor
mov esi,tytul
mov edi,bufor+320*4*(100-16)
call printfonttbl

call drop

mov ax,counter
cmp ax,4*70
jb pp1
