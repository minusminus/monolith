;obracanie punktow
;macierz obrotu 3x3
rotate proc
;mov esi,verttbl	   ;tablica pktow obiektu
;mov edi,wsp3d	      ;tablica pktow po obrocie -> wyjsciowa
;mov ebx,offset macierz 	;macierz obrotu
;mov ecx,vertexcount	 ;licznik

rotlup:
fld dword ptr[esi]	;x
fld dword ptr[esi+4]	;y
fld dword ptr[esi+8]	;z
fmul dword ptr[ebx+24]
fxch st(1)
fmul dword ptr[ebx+12]
fxch st(2)
fmul dword ptr[ebx+0]
fxch st(1)
faddp st(1),st
fxch st(1)
faddp st(1),st		;obrocony X
fld dword ptr[esi]	;x
fld dword ptr[esi+4]	;y
fld dword ptr[esi+8]	;z
fmul dword ptr[ebx+24+4]
fxch st(1)
fmul dword ptr[ebx+12+4]
fxch st(2)
fmul dword ptr[ebx+0+4]
fxch st(1)
faddp st(1),st
fxch st(1)
faddp st(1),st		;obrocony Y
fld dword ptr[esi]	;x
fld dword ptr[esi+4]	;y
fld dword ptr[esi+8]	;z
fmul dword ptr[ebx+24+8]
fxch st(1)
fmul dword ptr[ebx+12+8]
fxch st(2)
fmul dword ptr[ebx+0+8]
fxch st(1)
faddp st(1),st
fxch st(1)
faddp st(1),st		;obrocony Z
fxch st(1)
fstp dword ptr[edi+4]
fstp dword ptr[edi+8]
fstp dword ptr[edi]

add esi,4*6	;oryginalna -> x,y,z,nx,ny,nz
add edi,4*9	;x,y,z,x2d,y2d,nx,ny,nz,persp -> po obrocie
dec ecx
jnz rotlup

ret
endp


;obraca normalsy w przeciwna strone niz punkty
rotateback proc
rotlupB:
fld dword ptr[esi+12]	   ;x
fld dword ptr[esi+16]	 ;y
fld dword ptr[esi+20]	 ;z
fmul dword ptr[ebx+8]
fxch st(1)
fmul dword ptr[ebx+4]
fxch st(2)
fmul dword ptr[ebx]
fxch st(1)
faddp st(1),st
fxch st(1)
faddp st(1),st		;obrocony X
fld dword ptr[esi+12]	   ;x
fld dword ptr[esi+16]	 ;y
fld dword ptr[esi+20]	 ;z
fmul dword ptr[ebx+20]
fxch st(1)
fmul dword ptr[ebx+16]
fxch st(2)
fmul dword ptr[ebx+12]
fxch st(1)
faddp st(1),st
fxch st(1)
faddp st(1),st		;obrocony Y
fld dword ptr[esi+12]	   ;x
fld dword ptr[esi+16]	 ;y
fld dword ptr[esi+20]	 ;z
fmul dword ptr[ebx+32]
fxch st(1)
fmul dword ptr[ebx+28]
fxch st(2)
fmul dword ptr[ebx+24]
fxch st(1)
faddp st(1),st
fxch st(1)
faddp st(1),st		;obrocony Z
fxch st(1)
fadd dword ptr[l128]
fstp dword ptr[edi+24]
fadd dword ptr[l128]
fstp dword ptr[edi+28]
fadd dword ptr[l128]
fstp dword ptr[edi+20]

add esi,4*6
add edi,4*9
dec ecx
jnz rotlupB
ret
endp
