;rysuje bumpowany tunel
bumpytunel proc
mov edi,bufor
mov esi,tablicexy	;tablica tunelu
;mov dh,[y1adder]
;mov dl,[x1adder]
mov dx,word ptr[x1adder]
;mov bl,[x2adder]
;mov bh,[y2adder]
mov bx,word ptr[x2adder]
mov bp,320*200	       ;ilosc pktow ekranu

;movq mm5,qword ptr [m1]
db 0fh,6fh,2eh
dw offset m1

btloop:
mov eax,[esi]		;adres texturki w tunelu
mov ecx,[esi]		;adres do bumpmapy
add ah,dh
add ch,bh
add al,dl
add cl,bl
;texo: punpcklbw mm2,dword ptr [4*ecx+textunel]
db 67h,66h,0fh,60h,14h,8dh,00h,12h,7ah,00h
bumpo: mov ecx,[4*ecx+bumpmap]	     ;wez przesuniecie z bumpmapy
add ch,ah
add cl,al

;dodanie koloru [mmx version]
;psrlw mm2,8
db 0fh,71h,0d2h,08h
;paddw mm2,qword ptr [8*ecx+phmapext]
db 67h,0fh,0fdh,14h,0cdh,00h,12h,9dh,00h
;movq mm4,mm2
db 0fh,6fh,0e2h
;psraw mm4,16
db 0fh,71h,0e4h,10h
;pxor mm4,mm5
db 0fh,0efh,0e5h
;pand mm2,mm4
db 0fh,0dbh,0d4h
;packuswb mm0,mm2
db 0fh,67h,0c2h
;psrlq mm0,32
db 0fh,73h,0d0h,20h

;movd dword ptr [edi],mm0
db 67h,66h,0fh,7eh,07h

add edi,4
add esi,4
dec bp
jnz btloop

;emms
db 0fh,77h

ret
bumpytunel endp

;m1 dd -1,-1
