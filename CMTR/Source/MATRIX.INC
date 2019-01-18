;pommat1: dd 3*4 dup(0)
;pommat2: dd 3*4 dup(0)
;pommat3: dd 3*4 dup(0)
;omat dd 0
;emat dw 0
;sinsin dd 0
;kt dw 0
;lm1 dd -1.0

;----------------------------------------------------------------------
;----------------------------------------------------------------------
;----------------------------------------------------------------------
;translacja miacierzy [do obrotu normalsow]
;we:
;esi - macierz
;wy:
;obrocona macierz spod esi
;odwrocmac proc
;mov cx,4
;lea bx,[si+4*8]
;obinner:
;mov eax,[si]
;xchg eax,dword ptr[bx]
;mov [si],eax
;add si,4
;sub bx,4
;dec cx
;jnz obinner
;
;ret
;endp



;----------------------------------------------------------------------
;----------------------------------------------------------------------
;----------------------------------------------------------------------
;mnozenie wektorow 3x3
;we:
;esi - wektor poziomy
;edi - pionowy [jak w macierzy 3x3]
;ebx - wynik
;wy:
;wynik w [ebx]
vmulv proc
fld dword ptr[si]
fld dword ptr[si+4]
fld dword ptr[si+8]
fmul dword ptr[di+24]
fxch st(1)
fmul dword ptr[di+12]
fxch st(2)
fmul dword ptr[di]
fxch st(1)
faddp st(1),st
fxch st(1)
faddp st(1),st
fstp dword ptr[bx]
ret
endp



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
mov ax,di
mov bp,3
m33lup1:
mov cx,3
mov di,ax
m33lup2:
call vmulv
add bx,4
add di,4
dec cx
jnz m33lup2
add si,12
dec bp
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
push si
pop di
mov cx,9
xor eax,eax
rep stosd
fld1
fst dword ptr[si]
fst dword ptr[si+16]
fstp dword ptr[si+32]
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
;makemat PROC
;push bx
;push bp
;;przygotowanie macierzy obrotow
;mov si,offset pommat1
;call makeidentmatrix
;mov si,offset pommat2
;push si
;call makeidentmatrix
;pop di
;;mov di,offset pommat2
;;obrot Y
;fild dword ptr ds:[bp+4]
;fmul dword ptr[pi180]
;fsincos
;fst dword ptr[di]		 ;cosy
;fstp dword ptr[di+32]
;fst dword ptr[di+24]		 ;siny
;fchs
;fstp dword ptr[di+8]
;;obrot X
;mov si,offset pommat1
;fild dword ptr ds:[bp+0]
;fmul dword ptr[pi180]
;fsincos
;fst dword ptr[si+16]		 ;cosx
;fstp dword ptr[si+32]
;fst dword ptr[si+20]		 ;sinx
;fchs
;fstp dword ptr[si+28]
;mov bx,offset pommat3
;call matmul3x3
;;obrot Z
;mov si,offset pommat2
;push si
;call makeidentmatrix
;pop di
;;mov di,offset pommat2
;;mov bp,kt
;pop bp
;fild dword ptr ds:[bp+8]
;fmul dword ptr[pi180]
;fsincos
;fst dword ptr[di+0]		 ;cosz
;fstp dword ptr[di+16]
;fst dword ptr[di+4]		 ;sinz
;fchs
;fstp dword ptr[di+12]
;mov si,offset pommat3
;;mov bx,offset pommat1
;;mov bx,emat
;pop bx
;call matmul3x3
;ret
;endp
