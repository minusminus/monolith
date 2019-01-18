;oblicza normalsy w punktach i normalizuje
;porownuje adresy
wersory proc
mov ebx,wsp3d
mov edi,verttbl
mov ebp,vertexcount

mloop:
mov esi,facetbl
mov ecx,facecount
fldz
fldz
fldz
mov edx,0
lupcf:
mov eax,2
lup1:
;mov edi,[esi+4*eax]	 ;adres pktu
;cmp ebx,edi
cmp ebx,[esi+4*eax]
jne niema
inc edx   ;jest
fadd dword ptr[esi+16]	;nx
fxch st(2)
fadd dword ptr[esi+24]	;nz
fxch st(1)
fadd dword ptr[esi+20]	;ny
fxch st(1)
fxch st(2)
niema:
dec eax
jns lup1

add esi,4*8
dec ecx
jnz lupcf

mov fpuout,edx		;usrednianie normlasow
fild dword ptr[fpuout]
fld st
fld st
fdivp st(5),st
fdivp st(3),st
fdivp st(1),st
fst dword ptr[edi+12]	;zachowaj te normalsy
fxch st(1)
fst dword ptr[edi+16]
fxch st(2)
fst dword ptr[edi+20]
fmul st,st	      ;normalizacja
fxch st(1)
fmul st,st
fxch st(2)
fmul st,st
faddp st(2),st
faddp st(1),st
fsqrt	       ;dlugosc tego wektora

fld dword ptr[edi+12]
fmul dword ptr[l256]
fdiv st,st(1)
;fxch st(1)
fstp dword ptr[edi+12]
fld dword ptr[edi+16]
fmul dword ptr[l256]
fdiv st,st(1)
;fxch st(1)
fstp dword ptr[edi+16]
fld dword ptr[edi+20]
fmul dword ptr[l256]
fdivrp st(1),st
fstp dword ptr[edi+20]	;tu juz mamy znormalizowane wektory
;fstp st

add ebx,4*9	;nast pkt
add edi,4*6
dec ebp
jnz mloop

ret
endp

ll1 dd 1.0