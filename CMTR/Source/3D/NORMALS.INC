normals proc
;mov esi,facetbl
;mov ecx,facecount

normloop:
mov edi,[esi]
mov ebp,[esi+4]
mov ebx,[esi+8]
;tu liczenie normalsow
fld dword ptr[ebp+4]
fsub dword ptr[edi+4]
fld dword ptr[ebx+8]
fsub dword ptr[edi+8]
fmulp st(1),st
fld dword ptr[ebx+4]
fsub dword ptr[edi+4]
fld dword ptr[ebp+8]
fsub dword ptr[edi+8]
fmulp st(1),st
faddp st(1),st
fmul dword ptr[lm1]
fstp dword ptr[esi+16]	;xn
fld dword ptr[ebp+0]
fsub dword ptr[edi+0]
fld dword ptr[ebx+8]
fsub dword ptr[edi+8]
fmulp st(1),st
fld dword ptr[ebx+0]
fsub dword ptr[edi+0]
fld dword ptr[ebp+8]
fsub dword ptr[edi+8]
fmulp st(1),st
fsubp st(1),st
fstp dword ptr[esi+20]	    ;yn
fld dword ptr[ebp+4]
fsub dword ptr[edi+4]
fld dword ptr[ebx+0]
fsub dword ptr[edi+0]
fmulp st(1),st
fld dword ptr[ebx+4]
fsub dword ptr[edi+4]
fld dword ptr[ebp+0]
fsub dword ptr[edi+0]
fmulp st(1),st
faddp st(1),st
fmul dword ptr[lm1]
fstp dword ptr[esi+24]	   ;zn
add esi,4*8
dec ecx
jnz normloop

ret
endp