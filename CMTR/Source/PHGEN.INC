;generator phongmapy
;edi - bufor
mov edi,phmap
xor dx,dx
yphloop:
xor bp,bp
xphloop:
mov word ptr [fpuout],bp
fild word ptr [fpuout]
;fsub dword ptr [phxs]
fsub dword ptr [l128]
fmul st,st
mov word ptr [fpuout],dx
fild word ptr [fpuout]
;fsub dword ptr [phys]
fsub dword ptr [l128]
fmul st,st
faddp st(1),st		;D^2
fld dword ptr [phrr]	   ;r^2
fsubrp st(1),st
;fst dword ptr [fpuout]
;test byte ptr [fpuout+3],80h
;jz okphdl
;xor eax,eax
;fstp st
;jmp putphcol
;okphdl:
fsqrt			;sqrt(r^2-D^2)
fistp dword ptr [fpuout]
mov al,byte ptr [fpuout]
shl al,1
jnc okphkk
mov al,0ffh
okphkk:
mov ah,al
shl eax,8
mov al,ah
putphcol:
mov  [edi],eax

add edi,4
inc bp
cmp bp,256
jl xphloop
inc dx
cmp dx,256
jl yphloop
