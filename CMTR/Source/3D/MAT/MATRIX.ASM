pommat1: dd 3*4 dup(0)
pommat2: dd 3*4 dup(0)
pommat3: dd 3*4 dup(0)
omat dd 0
emat dd 0
sinsin dd 0
kt dd 0
lm1 dd -1.0

;----------------------------------------------------------------------
;----------------------------------------------------------------------
;----------------------------------------------------------------------
;mnozenie macierze 3x3
;we:
;esi - macierz L
;edi - macierz P
;ebx - macierz L*P
;wy:
;pod adresem podanym w ebx wynik mnozenia
matmul3x3 PROC
mov eax,edi
mov ebp,3
m33lup1:
mov ecx,3
mov edi,eax
m33lup2:
fld dword ptr[esi]
fld dword ptr[esi+4]
fld dword ptr[esi+8]
fmul dword ptr[edi+24]
fxch st(1)
fmul dword ptr[edi+12]
fxch st(2)
fmul dword ptr[edi]
fxch st(1)
faddp st(1),st
fxch st(1)
faddp st(1),st
fstp dword ptr[ebx]
add ebx,4
add edi,4
dec ecx
jnz m33lup2
add esi,12
dec ebp
jnz m33lup1
ret
endp


;----------------------------------------------------------------------
;----------------------------------------------------------------------
;----------------------------------------------------------------------
;tworzy macierz identycznosciowa 4x3 dolna kolumna wypelniona 0
;we:
;esi - macierz
;wy:
;pod adresem podanym w esi macierz jednostkowa
makeidentmatrix PROC
xor eax,eax
fld1
;wiersz 1
fst dword ptr[esi]
mov dword ptr[esi+4],eax
mov dword ptr[esi+8],eax
;wiersz 2
mov dword ptr[esi+12],eax
fst dword ptr[esi+16]
mov dword ptr[esi+20],eax
;wiersz 3
mov dword ptr[esi+24],eax
mov dword ptr[esi+28],eax
fstp dword ptr[esi+32]
;wiersz 4
;mov dword ptr[esi+36],eax
;mov dword ptr[esi+40],eax
;mov dword ptr[esi+44],eax
ret
endp


;----------------------------------------------------------------------
;----------------------------------------------------------------------
;----------------------------------------------------------------------
;tworzy macierz obrotu
;we:
;esi - macierz obiektu
;ebx - macierz wynikowa
;edx - tablica sinusow 360+90 stopni
;ebp - katy i translacje kx,ky,kz,tx,ty,tz dd
;wy:
;macierz wynikowa pod ebx
makemat PROC
mov omat,esi
mov emat,ebx
mov sinsin,edx
mov kt,ebp
;macierze identycznosciowe
;mov esi,omat
;call makeidentmatrix
mov esi,emat
call makeidentmatrix
;translacja
;mov ebp,kt
;mov esi,omat
;mov eax,[ebp+12]
;mov [esi+36],eax
;mov eax,[ebp+16]
;mov [esi+40],eax
;mov eax,[ebp+20]
;mov [esi+44],eax
;przygotowanie macierzy obrotow
mov esi,offset pommat1
call makeidentmatrix
mov esi,offset pommat2
call makeidentmatrix
mov ebx,sinsin
mov edi,offset pommat2
;obrot Y
mov edx,[ebp+4]
fld dword ptr[ebx+4*edx+0]	;siny
fst dword ptr[edi+24]
fmul dword ptr[lm1]
fstp dword ptr[edi+8]
fld dword ptr[ebx+4*edx+4*90]	;cosy
fst dword ptr[edi]
fstp dword ptr[edi+32]
;obrot X
mov esi,offset pommat1
mov edx,[ebp+0]
fld dword ptr[ebx+4*edx+0]	;sinx
fst dword ptr[esi+20]
fmul dword ptr[lm1]
fstp dword ptr[esi+28]
fld dword ptr[ebx+4*edx+90*4]	;cosx
fst dword ptr[esi+16]
fstp dword ptr[esi+32]
mov ebx,offset pommat3
call matmul3x3
;obrot Z
mov esi,offset pommat2
call makeidentmatrix
mov edi,offset pommat2
mov ebp,kt
mov ebx,sinsin
mov edx,[ebp+8]
fld dword ptr[ebx+4*edx]	;sinz
fst dword ptr[edi+4]
fmul dword ptr[lm1]
fstp dword ptr[edi+12]
fld dword ptr[ebx+4*edx+4*90]	;cosz
fst dword ptr[edi+0]
fstp dword ptr[edi+16]
mov esi,offset pommat3
mov ebx,offset pommat1
call matmul3x3
;eye matrix obiektu
;mov esi,omat
;mov edi,offset pommat1
;mov ebx,emat
;call matmul4x3
mov esi,offset pommat1
mov edi,emat
mov ecx,9
cld
rep movsd
ret
endp
