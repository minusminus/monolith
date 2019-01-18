.586
code32 segment use32 para public 'code'
assume cs:code32,ds:code32,es:code32

;org 100h
;start:

public envy
public initenvy

;we:
;esi - adres face'a
envy proc
;ladowanie rejestrow adresami pktow
mov edi,[esi+0]      ;p1
mov ebp,[esi+4]      ;p2
mov edx,[esi+8]      ;p3
mov esi,fastdivtbl   ;tablica do szybkiego dzielenia
;jmp here

;sortowanie po y
fld dword ptr[edi+16]	;y1  wszystkie wspolrzedne do 2d oczywiscie
fistp dword ptr[fpuout]
mov eax,fpuout
fld dword ptr[ebp+16]	;y2
fistp dword ptr[fpuout]
mov ebx,fpuout
fld dword ptr[edx+16]
fistp dword ptr[fpuout] ;y3
mov ecx,fpuout
cmp eax,ebx
jle noch12
xchg eax,ebx
xchg edi,ebp
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
fld dword ptr[ebp+16]
fld dword ptr[ebp+12]
fld dword ptr[edx+16]	;y3 x2 y2 x3
fsub dword ptr[edi+16]	;y3-y1
fxch st(1)
fsub dword ptr[edi+12]	;x2-x1
fxch st(2)
fsub dword ptr[edi+16]	;y3-y1
fxch st(3)
fsub dword ptr[edi+12]	;x3-x1
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
mov dword ptr staleNx[2],eax
mov ecx,24
call stalainterp	;stale Ny
mov eax,dword ptr[fpuout]
;ror eax,16
mov dword ptr staleNy[2],eax
fstp st

here:

;liczenie delt w trojkacie
;fld dword ptr[edi+12]
;fadd qword ptr[magic]
;fstp qword ptr[fpuout]
;mov eax,dword ptr[fpuout]
;mov tempx,eax		   ;przy okazji konwersja x1 jakby nie bylo czesci12
fld dword ptr[edx+12]
fld dword ptr[edx+16]
fsub dword ptr[edi+16] ;y3-y1
fxch st(1)
fsub dword ptr[edi+12]	;x3-x1
fxch st(1)
call fastdiv		;(x3-x1)/(y3-y1)
;fadd qword ptr[magic]
;fstp qword ptr[fpuout]
mov ecx,dword ptr[fpuout]
fld dword ptr[edx+12]
fld dword ptr[edx+16]
fsub dword ptr[ebp+16] ;y3-y2
fist dword ptr[fpuout]
mov eax,fpuout
;or eax,eax	 ;czy rysowac czesc 32
;jnz jest32
cmp eax,0
jg jest32
mov  byte ptr[czesci],0 ;nie ma czesci32
jmp ddd32
jest32:
mov byte ptr[czesci],10b  ;jest 32
ddd32:
fxch st(1)
fsub dword ptr[ebp+12]	;x3-x2
fxch st(1)
call fastdiv		;(x3-x2)/(y3-y2)
mov ebx,dword ptr[fpuout]
fld dword ptr[ebp+12]
fld dword ptr[ebp+16]
fsub dword ptr[edi+16] ;y2-y1
fist dword ptr[fpuout]
mov eax,fpuout
;or eax,eax	 ;czy rysowac czesc 21
;jnz jest21
cmp eax,0
jg jest21
or  byte ptr[czesci],0 ;nie ma czesci12
jmp ddd21
jest21:
or byte ptr[czesci],1  ;jest 21
ddd21:
fxch st(1)
fsub dword ptr[edi+12]	;x2-x1
fxch st(1)
call fastdiv		;(x2-x1)/(y2-y1)
mov eax,dword ptr[fpuout]

;porownanie delt i odpowiednie wstawienie
cmp ecx,eax
jl odwrotnie21
mov dword ptr d21[2],eax
mov dword ptr d31[2],ecx
jmp porpor32
odwrotnie21:
mov dword ptr d21[2],ecx
mov dword ptr d31[2],eax
porpor32:
cmp ecx,ebx
jg odwrotnie32
mov dword ptr d32[2],ebx
mov dword ptr d31x[2],ecx
;jmp czesc21
;jmp odwrotnie
jmp liczdelty
odwrotnie32:
mov dword ptr d32[2],ecx
mov dword ptr d31x[2],ebx
jmp odwrotnie

;here:

liczdelty:
;liczenie delt Nx,Ny dla czesci 12
fld dword ptr[ebp+20]
fld dword ptr[ebp+16]
fsub dword ptr[edi+16] ;y2-y1
fxch st(1)
fsub dword ptr[edi+20]	;Nx2-Nx1
fxch st(1)
call fastdiv		;(Nx2-Nx1)/(y2-y1)
mov eax,dword ptr[fpuout]
;ror eax,16
mov dword ptr nxd21[2],eax
fld dword ptr[ebp+24]
fld dword ptr[ebp+16]
fsub dword ptr[edi+16] ;y2-y1
fxch st(1)
fsub dword ptr[edi+24]	;Ny2-Ny1
fxch st(1)
call fastdiv		;(Ny2-Ny1)/(y2-y1)
mov eax,dword ptr[fpuout]
;ror eax,16
mov dword ptr nyd21[2],eax

;liczenie delt Nx,Ny dla czesci 23
fld dword ptr[edx+20]
fld dword ptr[edx+16]
fsub dword ptr[ebp+16] ;y3-y2
fxch st(1)
fsub dword ptr[ebp+20]	;Nx3-Nx2
fxch st(1)
call fastdiv		;(Nx3-Nx2)/(y3-y2)
mov eax,dword ptr[fpuout]
;ror eax,16
mov dword ptr nxd32[2],eax
fld dword ptr[edx+24]
fld dword ptr[edx+16]
fsub dword ptr[ebp+16] ;y3-y2
fxch st(1)
fsub dword ptr[ebp+24]	;Ny3-Ny2
fxch st(1)
call fastdiv		;(Ny3-Ny2)/(y3-y2)
mov eax,dword ptr[fpuout]
;ror eax,16
mov dword ptr nyd32[2],eax
jmp czesc21

odwrotnie:
;liczenie delt Nx,Ny dla obu czesci po krawedzi 13
fld dword ptr[edx+20]
fld dword ptr[edx+16]
fsub dword ptr[edi+16] ;y3-y1
fxch st(1)
fsub dword ptr[edi+20]	;Nx3-Nx1
fxch st(1)
call fastdiv		;(Nx3-Nx1)/(y3-y1)
mov eax,dword ptr[fpuout]
;ror eax,16
mov dword ptr nxd21[2],eax
mov dword ptr nxd32[2],eax
fld dword ptr[edx+24]
fld dword ptr[edx+16]
fsub dword ptr[edi+16] ;y3-y1
fxch st(1)
fsub dword ptr[edi+24]	;Ny3-Ny1
fxch st(1)
call fastdiv		;(Ny3-Ny1)/(y3-y1)
mov eax,dword ptr[fpuout]
;ror eax,16
mov dword ptr nyd21[2],eax
mov dword ptr nyd32[2],eax

;rysowanie czesci 21
czesc21:
test byte ptr[czesci],1
jz czesc23		;jak nie rysowac to skocz
;liczenie delt Nx,Ny

;rysowanie polowki face'a
pushad
fld dword ptr[ebp+16]
fsub dword ptr[edi+16]	;y2-y1 = licznik
fistp dword ptr[fpuout]
mov esi,fpuout
;inc esi
fld dword ptr[edi+12]	;x1
;fistp dword ptr[fpuout]
fadd qword ptr[magic]
fstp qword ptr[fpuout]
mov ecx,dword ptr[fpuout]
mov ebp,ecx
fld dword ptr[edi+20]	;nx1
fadd qword ptr[magic]
fstp qword ptr[fpuout]
mov ebx,dword ptr[fpuout]
;ror ebx,16
fld dword ptr[edi+24]	;ny1
fadd qword ptr[magic]
fstp qword ptr[fpuout]
mov edx,dword ptr[fpuout]
;ror edx,16
fld dword ptr[edi+16]	;y1
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
emms
popad

;czesc 32
czesc23:
mov esi,fastdivtbl
test byte ptr[czesci],10b
jz koniecenvy		   ;jak nie rysowac to skocz
;liczenie delt Nx,Ny

;rysowanie polowki face'a
pushad
fld dword ptr[edx+16]
fsub dword ptr[ebp+16]	;y3-y2 = licznik
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
emms
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
fld dword ptr[ebp+16]
fld dword ptr[ebp+ecx]
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
fistp dword ptr[fpuout]
mov eax,fpuout
fmul dword ptr[esi+4*eax]
fadd qword ptr[magic]		;od razu zdejmij
fstp qword ptr[fpuout]
ret
fastdiv endp



;we:
;eax - 0
;ecx - licznik
;ebp - poczatkowy x
;ebx - nx 16:16 ror
;edx - ny 16:16 ror
envylinedraw proc
filup:
push ebx
push edx
shr ebx,16
shr edx,16
mov al,bl
mov ah,dl
phmap:movd mm0,dword ptr[4*eax+12345678h]
envmap:movd mm1,dword ptr[4*eax+12345678h]
;paddusb mm0,mm1
movd dword ptr[edi+4*ebp],mm0
pop edx
pop ebx
stalenx: add ebx,12345678h
staleny: add edx,12345678h
inc ebp
dec ecx
jnz filup
ret
envylinedraw endp

;shit dd 00ffffffh


czesci db ?	;ktore czesci do rysowania
l320x4 dd 1280.0
fpuout dd ?,?
ll1 dd 1.0
;fastdivtbl dd ?
;magic dd ?,?
;tempx dd ?
;bufor dd ?

extrn envm :dword
extrn phm:dword
extrn bufor:dword
extrn magic:qword
extrn fastdivtbl:dword
extrn vesabuf:dword

initenvy proc
mov eax,envm
mov dword ptr envmap[4],eax
mov eax,phm
mov dword ptr phmap[4],eax
ret
initenvy endp


lm1 dd -1.0

code32 ends
end