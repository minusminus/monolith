;procedura tworzaca macierz obrotu dla obiektu
makerotmatrix proc
;laduje sinusy i cosinusy
;mov esi,sintbl
;mov eax,alfa
;mov ebx,beta
;mov ecx,gamma
;mov edi,offset macierz

;precalcs
fld dword ptr[esi+4*ecx+90*4]	     ;c3
fld dword ptr[esi+4*ecx]	     ;s3
fld st				     ;s3
fld st(2)			     ;c3
fmul dword ptr[esi+4*eax]	     ;c3s1
fxch st(1)
fmul dword ptr[esi+4*eax]	     ;s3s1
fxch st(3)
fmul dword ptr[esi+4*eax+90*4]	     ;c3c1
fxch st(2)
fmul dword ptr[esi+4*eax+90*4]	     ;s3c1
fxch st(1)
fstp dword ptr[c3s1]
fstp dword ptr[s3c1]
fstp dword ptr[c3c1]
fstp dword ptr[s3s1]

;juz liczenie
fld dword ptr[esi+4*ebx+90*4]		;c2
fld st
fld st
fld st
fmul dword ptr[esi+4*eax]		;c2s1
fxch st(1)
fmul dword ptr[esi+4*eax+90*4]		;c2c1
fxch st(2)
fmul dword ptr[esi+4*ecx]		;c2s3
fxch st(3)
fmul dword ptr[esi+4*ecx+90*4]		;c2c3
fxch st(1)
fmul dword ptr[lm1]			;-c2s1
fxch st(3)
fmul dword ptr[lm1]			;-c2s3
fxch st(1)
fstp dword ptr[edi+0]
fstp dword ptr[edi+4]
fstp dword ptr[edi+32]
fstp dword ptr[edi+20]

fld dword ptr[c3s1]			;A
fld dword ptr[s3c1]			;B
fmul dword ptr[esi+4*ebx]		;Bs2
fxch st(1)
fmul dword ptr[esi+4*ebx]		;As2
fxch st(1)
fsubr dword ptr[c3s1]			;-Bs2+A
fxch st(1)
fsubr dword ptr[s3c1]			;-Bs2+A
fxch st(1)
fstp dword ptr[edi+12]
fstp dword ptr[edi+28]

fld dword ptr[c3c1]			;C
fld dword ptr[s3s1]			;D
fmul dword ptr[esi+4*ebx]		;Ds2
fxch st(1)
fmul dword ptr[esi+4*ebx]		;Cs2
fxch st(1)
fadd dword ptr[c3c1]		       ;Ds2+C
fxch st(1)
fadd dword ptr[s3s1]		       ;Ds2+C
fxch st(1)
fstp dword ptr[edi+16]
fstp dword ptr[edi+24]

fld dword ptr[esi+4*ebx]
fmul dword ptr[lm1]			;-s2
fstp dword ptr[edi+8]

ret
endp