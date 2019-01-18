tunxs equ -160
tunys equ -100

;generator proc
mov esi,tablicexy
xor ebx,ebx
mov dx,tunys
mov bp,200     ;licznik y
glupy:
mov di,tunxs
mov cx,320     ;licznik x
glupx:
mov word ptr[x],di
mov word ptr[y],dx

fild word ptr [x]
fild word ptr [y]
fpatan
fmul dword ptr [l256]
fldpi
fdivp st(1),st
fistp dword ptr [fpuout]
;mov ax,word ptr[fpuout]
mov bh,byte ptr[fpuout]

fild word ptr [x]
fmul st,st
fild word ptr [y]
fmul st,st
faddp st(1),st
fsqrt
fild dword ptr [radius]
fdivrp st(1),st
fistp dword ptr [fpuout]
;mov bx,word ptr[fpuout]
;mov bh,al
mov bl,byte ptr[fpuout]
;and ebx,0ffffh
mov [esi],ebx
add esi,4

inc di
dec cx
jnz glupx
inc dx
dec bp
jnz glupy

;ret
;endp