;normals proc
;mov esi,facetbl
;mov ecx,facecount

normloop:
mov di,[si]
mov bp,[si+4]
mov bx,[si+8]
;tu liczenie normalsow
fld dword ptr ds:[bp+4]
fsub dword ptr[di+4]
fld dword ptr[bx+8]
fsub dword ptr[di+8]
fmulp st(1),st
fld dword ptr[bx+4]
fsub dword ptr[di+4]
fld dword ptr ds:[bp+8]
fsub dword ptr[di+8]
fmulp st(1),st
faddp st(1),st
;fmul dword ptr[lm1]
fchs
fstp dword ptr[si+16]  ;xn
fld dword ptr ds:[bp+0]
fsub dword ptr[di+0]
fld dword ptr[bx+8]
fsub dword ptr[di+8]
fmulp st(1),st
fld dword ptr[bx+0]
fsub dword ptr[di+0]
fld dword ptr ds:[bp+8]
fsub dword ptr[di+8]
fmulp st(1),st
fsubp st(1),st
fstp dword ptr[si+20]	   ;yn
fld dword ptr ds:[bp+4]
fsub dword ptr[di+4]
fld dword ptr[bx+0]
fsub dword ptr[di+0]
fmulp st(1),st
fld dword ptr[bx+4]
fsub dword ptr[di+4]
fld dword ptr ds:[bp+0]
fsub dword ptr[di+0]
fmulp st(1),st
faddp st(1),st
;fmul dword ptr[lm1]
fchs
fstp dword ptr[si+24]	  ;zn
add si,4*8
dec cx
jnz normloop

;ret
;endp

