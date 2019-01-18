;extrn envylinedraw:near
;extrn stalenx:dword
;extrn staleny:dword

;we:
;esi - adres face'a
envy proc
xor edi,edi
xor ebp,ebp

;ladowanie rejestrow adresami pktow
mov di,[si+0]	   ;p1
mov bp,[si+4]	   ;p2
mov edx,[si+8]	    ;p3
;mov esi,fastdivtbl   ;tablica do szybkiego dzielenia
;jmp here

;sortowanie po y
fld dword ptr[di+16]   ;y1  wszystkie wspolrzedne do 2d oczywiscie
fistp dword ptr[fpuout]
mov eax,fpuout
fld dword ptr ds:[bp+16]   ;y2
fistp dword ptr[fpuout]
mov ebx,fpuout
fld dword ptr[edx+16]
fistp dword ptr[fpuout] ;y3
mov ecx,fpuout
cmp eax,ebx
jle noch12
xchg eax,ebx
xchg di,bp
noch12:
cmp eax,ecx
jle noch13
xchg eax,ecx
xchg edi,edx
noch13:
cmp ebx,ecx
jle noch23
xchg ebp,edx
xchg ebx,ecx
noch23:
;sprawdzenie czy jest sens rysowac calego face'a
sub eax,ecx
jz koniecenvy

;here:

;rysujemy wiec liczymy stale przyrosty normalsow w X
fld dword ptr[edx+12]
fld dword ptr ds:[bp+16]
fld dword ptr ds:[bp+12]
fld dword ptr[edx+16]	;y3 x2 y2 x3
fsub dword ptr[di+16]  ;y3-y1
fxch st(1)
fsub dword ptr[di+12]  ;x2-x1
fxch st(2)
fsub dword ptr[di+16]  ;y3-y1
fxch st(3)
fsub dword ptr[di+12]  ;x3-x1
fxch st(1)
fmulp st(2),st		;(y3-y1)(x2-x1)
fxch st(2)
fmulp st(2),st		;(y2-y1)(x3-x1)
fxch st(1)
fsubrp st(1),st
fld1
fdivrp st(1),st 	;1/[ta wartosc]
mov ecx,20		;offset do Nx
call stalainterp	;licz stala dla Nx
mov eax,dword ptr[fpuout]
;ror eax,16
mov dword ptr staleNx[3],eax
mov ecx,24
call stalainterp	;stale Ny
mov eax,dword ptr[fpuout]
;ror eax,16
mov dword ptr staleNy[3],eax
fstp st

;liczenie delt w trojkacie
;fld dword ptr[edi+12]
;fadd qword ptr[magic]
;fstp qword ptr[fpuout]
;mov eax,dword ptr[fpuout]
;mov tempx,eax		   ;przy okazji konwersja x1 jakby nie bylo czesci12
fld dword ptr[edx+12]
fld dword ptr[edx+16]
fsub dword ptr[di+16] ;y3-y1
fxch st(1)
fsub dword ptr[di+12]  ;x3-x1
fxch st(1)
call fastdiv		;(x3-x1)/(y3-y1)
mov ecx,dword ptr[fpuout]
fld dword ptr[edx+12]
fld dword ptr[edx+16]
fsub dword ptr ds:[bp+16] ;y3-y2
fist dword ptr[fpuout]
;mov eax,fpuout
;or eax,eax	 ;czy rysowac czesc 32
;jnz jest32
;cmp eax,0
cmp dword ptr[fpuout],0
jg jest32
mov  byte ptr[czesci],0 ;nie ma czesci32
jmp ddd32
jest32:
mov byte ptr[czesci],10b  ;jest 32
ddd32:
fxch st(1)
fsub dword ptr ds:[bp+12]  ;x3-x2
fxch st(1)
call fastdiv		;(x3-x2)/(y3-y2)
mov ebx,dword ptr[fpuout]
fld dword ptr ds:[bp+12]
fld dword ptr ds:[bp+16]
fsub dword ptr[di+16] ;y2-y1
fist dword ptr[fpuout]
;mov eax,fpuout
;or eax,eax	 ;czy rysowac czesc 21
;jnz jest21
;cmp eax,0
cmp dword ptr[fpuout],0
jg jest21
or  byte ptr[czesci],0 ;nie ma czesci12
jmp ddd21
jest21:
or byte ptr[czesci],1  ;jest 21
ddd21:
fxch st(1)
fsub dword ptr[di+12]  ;x2-x1
fxch st(1)
call fastdiv		;(x2-x1)/(y2-y1)
mov eax,dword ptr[fpuout]

;porownanie delt i odpowiednie wstawienie
cmp ecx,eax
jl odwrotnie21
mov dword ptr d21[3],eax
mov dword ptr d31[3],ecx
jmp porpor32
odwrotnie21:
mov dword ptr d21[3],ecx
mov dword ptr d31[3],eax
porpor32:
cmp ecx,ebx
jg odwrotnie32
mov dword ptr d32[3],ebx
mov dword ptr d31x[3],ecx
;jmp czesc21
;jmp odwrotnie
jmp liczdelty
odwrotnie32:
mov dword ptr d32[3],ecx
mov dword ptr d31x[3],ebx
jmp odwrotnie

;here:

liczdelty:
;liczenie delt Nx,Ny dla czesci 12
fld dword ptr ds:[bp+20]
fld dword ptr ds:[bp+16]
fsub dword ptr[di+16] ;y2-y1
fxch st(1)
fsub dword ptr[di+20]  ;Nx2-Nx1
fxch st(1)
call fastdiv		;(Nx2-Nx1)/(y2-y1)
mov eax,dword ptr[fpuout]
;ror eax,16
mov dword ptr nxd21[3],eax
fld dword ptr ds:[bp+24]
fld dword ptr ds:[bp+16]
fsub dword ptr[di+16] ;y2-y1
fxch st(1)
fsub dword ptr[di+24]  ;Ny2-Ny1
fxch st(1)
call fastdiv		;(Ny2-Ny1)/(y2-y1)
mov eax,dword ptr[fpuout]
;ror eax,16
mov dword ptr nyd21[3],eax

;liczenie delt Nx,Ny dla czesci 23
fld dword ptr[edx+20]
fld dword ptr[edx+16]
fsub dword ptr ds:[bp+16] ;y3-y2
fxch st(1)
fsub dword ptr ds:[bp+20]  ;Nx3-Nx2
fxch st(1)
call fastdiv		;(Nx3-Nx2)/(y3-y2)
mov eax,dword ptr[fpuout]
;ror eax,16
mov dword ptr nxd32[3],eax
fld dword ptr[edx+24]
fld dword ptr[edx+16]
fsub dword ptr ds:[bp+16] ;y3-y2
fxch st(1)
fsub dword ptr ds:[bp+24]  ;Ny3-Ny2
fxch st(1)
call fastdiv		;(Ny3-Ny2)/(y3-y2)
mov eax,dword ptr[fpuout]
;ror eax,16
mov dword ptr nyd32[3],eax
jmp czesc21

odwrotnie:
;mov dword ptr d21[2],ecx
;mov dword ptr d32[2],ecx
;mov dword ptr d31[2],eax
;mov dword ptr d31x[2],ebx
;liczenie delt Nx,Ny dla obu czesci po krawedzi 13
fld dword ptr[edx+20]
fld dword ptr[edx+16]
fsub dword ptr[di+16] ;y3-y1
fxch st(1)
fsub dword ptr[di+20]  ;Nx3-Nx1
fxch st(1)
call fastdiv		;(Nx3-Nx1)/(y3-y1)
mov eax,dword ptr[fpuout]
;ror eax,16
mov dword ptr nxd21[3],eax
mov dword ptr nxd32[3],eax
fld dword ptr[edx+24]
fld dword ptr[edx+16]
fsub dword ptr[di+16] ;y3-y1
fxch st(1)
fsub dword ptr[di+24]  ;Ny3-Ny1
fxch st(1)
call fastdiv		;(Ny3-Ny1)/(y3-y1)
mov eax,dword ptr[fpuout]
;ror eax,16
mov dword ptr nyd21[3],eax
mov dword ptr nyd32[3],eax

;rysowanie czesci 21
czesc21:
test byte ptr[czesci],1
jz czesc23		;jak nie rysowac to skocz
;liczenie delt Nx,Ny

;rysowanie polowki face'a
pushad
fld dword ptr ds:[bp+16]
fsub dword ptr[di+16]  ;y2-y1 = licznik
fistp dword ptr[fpuout]
mov esi,fpuout
;inc esi
fld dword ptr[di+12]   ;x1
;fistp dword ptr[fpuout]
fadd qword ptr[magic]
fstp qword ptr[fpuout]
mov ecx,dword ptr[fpuout]
mov ebp,ecx
fld dword ptr[di+20]   ;nx1
fadd qword ptr[magic]
fstp qword ptr[fpuout]
mov ebx,dword ptr[fpuout]
;ror ebx,16
fld dword ptr[di+24]   ;ny1
fadd qword ptr[magic]
fstp qword ptr[fpuout]
mov edx,dword ptr[fpuout]
;ror edx,16
fld dword ptr[di+16]   ;y1
;fmul dword ptr[l320x4]  ;y1*320*4 = adres w buforze
fistp dword ptr[fpuout]
mov edi,fpuout
imul edi,320*4
;add edi,bufor		 ;+ adres bufora
add edi,bufor		;+ adres bufora
;add edi,vesabuf
xor eax,eax
luup21:
push ebp
push ecx
push ebx
push edx
sub ecx,ebp
shr ecx,16
shr ebp,16
inc ecx
drawer: call envylinedraw
;clc
pop edx
pop ebx
pop ecx
pop ebp
nxd21: add ebx,12345678h
nyd21: add edx,12345678h
d31: add ecx,12345678h
d21: add ebp,12345678h
add edi,320*4		 ;nast linia
dec esi
jns luup21
;mov tempx,ecx
;emms
db 0fh,77h
popad

;czesc 32
czesc23:
;mov esi,fastdivtbl
test byte ptr[czesci],10b
jz koniecenvy		   ;jak nie rysowac to skocz
;liczenie delt Nx,Ny

;rysowanie polowki face'a
pushad
fld dword ptr[edx+16]
fsub dword ptr ds:[bp+16]  ;y3-y2 = licznik
fistp dword ptr[fpuout]
mov esi,fpuout
fld dword ptr[edx+12]	;x2
fadd qword ptr[magic]
fstp qword ptr[fpuout]
mov ebp,dword ptr[fpuout]
mov ecx,ebp
fld dword ptr[edx+20]	;nx2
fadd qword ptr[magic]
fstp qword ptr[fpuout]
mov ebx,dword ptr[fpuout]
;ror ebx,16
;fld dword ptr[edx+24]	 ;ny2
;fadd qword ptr[magic]
;fstp qword ptr[fpuout]
;mov edx,dword ptr[fpuout]
;ror edx,16
fld dword ptr[edx+16]	;y2
;fmul dword ptr[l320x4]  ;y2*320*4 = adres w buforze
fistp dword ptr[fpuout]
mov edi,fpuout
imul edi,320*4
add edi,bufor		;+ adres bufora
;add edi,vesabuf
fld dword ptr[edx+24]	;ny2
fadd qword ptr[magic]
fstp qword ptr[fpuout]
mov edx,dword ptr[fpuout]
;ror edx,16
xor eax,eax
luup32:
push ebp
push ecx
push ebx
push edx
sub ecx,ebp
shr ecx,16
shr ebp,16
inc ecx
drawer2: call envylinedraw
;clc
pop edx
pop ebx
pop ecx
pop ebp
nxd32: sub ebx,12345678h
nyd32: sub edx,12345678h
d31x: sub ecx,12345678h
d32: sub ebp,12345678h
sub edi,320*4		 ;nast linia
dec esi
jnz luup32
;emms
db 0fh,77h
popad


koniecenvy:
;push eax
;mov eax,shit
;sub eax,040404h
;mov shit,eax
;pop eax

ret
envy endp


;we: st(0) - 1/z
;    rejestry z adresami poszczegolnych pktow
stalainterp proc
fld dword ptr[edx+ecx]
fld dword ptr ds:[ebp+16]
fld dword ptr ds:[ebp+ecx]
fld dword ptr[edx+16]	;y3 nx2 y2 nx3 1/z
fsub dword ptr[edi+16]
fxch st(1)
fsub dword ptr[edi+ecx]
fxch st(2)
fsub dword ptr[edi+16]
fxch st(3)
fsub dword ptr[edi+ecx]
fxch st(1)
fmulp st(2),st
fxch st(2)
fmulp st(2),st
fxch st(1)
fsubrp st(1),st 	;w 1/z
fld st(1)
fmulp st(1),st
fadd qword ptr[magic]
fstp qword ptr[fpuout]
ret
stalainterp endp

;we:
;st(1)/st(0) bedzie wynikiem
;esi - fastdivtbl
fastdiv proc
fst dword ptr[fpuout]
cmp dword ptr[fpuout],0
jne okffd
fld1
faddp st(1),st

okffd:
fdivp st(1),st
;fistp dword ptr[fpuout]
;mov eax,fpuout
;fmul dword ptr[esi+4*eax]
fadd qword ptr[magic]		;od razu zdejmij
fstp qword ptr[fpuout]
ret
fastdiv endp




czesci db 0	;ktore czesci do rysowania
;l320x4 dd 1280.0


envylinedraw proc
;movd mm7,dword ptr[fontcol]
db 66h,0fh,6eh,3eh
dw faddr;52h,14h
filup:
push ebx
push edx
shr ebx,16
shr edx,16
mov bh,dl
;movd mm1,dword ptr ds:[4*ebx+tex3]	 ;envmapa
db 67h,66h,0fh,6eh,0ch,9dh,00h,12h,92h,00h
;paddusb mm1,mm7
db 0fh,0dch,0cfh
;movd dword ptr ds:[edi+4*ebp],mm1
db 67h,66h,0fh,7eh,0ch,0afh
pop edx
pop ebx
stalenx: add ebx,12345678h
staleny: add edx,12345678h
inc ebp
dec ecx
jnz filup
ret
envylinedraw endp
