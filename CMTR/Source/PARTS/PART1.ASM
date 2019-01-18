;poczatkowy tunel
;extrn bumpytunel:near
mov counter,0
mov fontflash,0

pp1:
call bumpytunel
;mov dword ptr fontcol[0],00ff00ffh
;mov dword ptr fontcol[4],00ff00ffh
;mov esi,tytul
;mov edi,bufor+320*4*(100-16)
;call printfonttbl
mov bx,5
mov ax,fontflash
shr ax,6
cwd
idiv bx
mov bx,dx
mov byte ptr flashcol[bx],0ffh

xor bx,bx
call makefontcolor
sub byte ptr flashcol[bx],4
mov esi,tytul
mov edi,bufor+320*4*(100-16)
call printfonttbl

call drop

mov ax,counter
;cmp ax,4*60
cmp ax,2*60
jb pp1
