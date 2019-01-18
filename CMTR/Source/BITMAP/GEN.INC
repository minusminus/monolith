;generator wezlow
generuj proc
mov esi,wezly
mov ebp,26
mov dword ptr[y],0c2c80000h	;-100.0

;fild dword ptr[start]		 ;start*PI/180
;fmul dword ptr[pi180]		 ;bo tylko taki jest
;fistp dword ptr[fpuout]	 ;wiec mozna policzyc przed petla
mov eax,start			 ;modulo 360
cdq
mov ebx,360
div ebx
mov ebx,edx
mov edi,sintbl		;tablica sinusow 360+90 pozycji

yglup:
mov ecx,41
mov dword ptr[x],0c3200000h	 ;-160.0
xglup:

include kula.inc
;include greetsy.inc

add esi,8		;nast wezel
fld dword ptr[x]	;zwieksz X
fadd dword ptr[l8]
fstp dword ptr[x]
dec ecx
jnz xglup
fld dword ptr[y]	;zwieksz Y
fadd dword ptr[l8]
fstp dword ptr[y]
dec ebp
jnz yglup

ret
endp

include greetsy2.inc



x dd ?
y dd ?
xt dd ?
yt dd ?
wz dd ?
radius dd ?
start dd ?
pi180 dd 0.017453292519943296
l8 dd 8.0
fpuout dd ?
l40000 dd 40000.0
l256 dd 256.0
l190 dd 190.0
l100 dd 100.0
l1000 dd 1000.0
l1_8 dd 0.25
lA dd ?
lB dd ?
lC dd ?
lD dd ?
llE dd ?