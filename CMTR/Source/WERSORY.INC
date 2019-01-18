;oblicza normalsy w punktach i normalizuje
;porownuje adresy
;wersory proc
mov ax,offset wsp3d
mov di,offset verttbl
mov bp,vertexcount

mloop:
mov si,offset facetbl
mov cx,facecount
fldz
fldz
fldz
xor dx,dx
lupcf:
mov bx,2*4
lup1:
cmp ax,[si+bx]		;porownaj adres pktu
jne niema
inc dx	 ;jest
fadd dword ptr[si+16]  ;nx
fxch st(2)
fadd dword ptr[si+24]  ;nz
fxch st(1)
fadd dword ptr[si+20]  ;ny
fxch st(1)
fxch st(2)
niema:
sub bx,4
jns lup1

add si,4*8
dec cx
jnz lupcf

mov word ptr[fpuout],dx 	 ;usrednianie normlasow
fild word ptr[fpuout]
fld st
fld st
fdivp st(5),st
fdivp st(3),st
fdivp st(1),st
fst dword ptr[di+12]   ;zachowaj te normalsy
fxch st(1)
fst dword ptr[di+16]
fxch st(2)
fst dword ptr[di+20]
fmul st,st	      ;normalizacja
fxch st(1)
fmul st,st
fxch st(2)
fmul st,st
faddp st(2),st
faddp st(1),st
fsqrt	       ;dlugosc tego wektora

fld dword ptr[di+12]
fmul dword ptr[l128]
fdiv st,st(1)
;fxch st(1)
fstp dword ptr[di+12]
fld dword ptr[di+16]
fmul dword ptr[l128]
fdiv st,st(1)
;fxch st(1)
fstp dword ptr[di+16]
fld dword ptr[di+20]
fmul dword ptr[l128]
fdivrp st(1),st
fstp dword ptr[di+20]  ;tu juz mamy znormalizowane wektory
;fstp st

add ax,4*9     ;nast pkt
add di,4*6
dec bp
jnz mloop

;ret
;endp
