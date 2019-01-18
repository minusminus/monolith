;generator wezlow
;ax - procedura do generacji
generuj proc
mov esi,wezly
mov bp,26
mov dword ptr[y],0c2c80000h	;-100.0

;fild dword ptr[start]		 ;start*PI/180
;fmul dword ptr[pi180]		 ;bo tylko taki jest
;fistp dword ptr[fpuout]	 ;wiec mozna policzyc przed petla
push ax
mov eax,startN			  ;modulo 360
cdq
mov ebx,360
div ebx
;mov ebx,edx
mov word ptr[fpuout],dx
;mov edi,sintbl 	 ;tablica sinusow 360+90 pozycji
pop ax

yglup:
mov cx,41
mov dword ptr[x],0c3200000h	 ;-160.0
xglup:

call ax
;include kula.inc
;include greetsy.inc

add esi,8		;nast wezel
fld dword ptr[x]	;zwieksz X
fadd dword ptr[l8]
fstp dword ptr[x]
dec cx
jnz xglup
fld dword ptr[y]	;zwieksz Y
fadd dword ptr[l8]
fstp dword ptr[y]
dec bp
jnz yglup

ret
endp

;include greetsy2.inc



;x dd 0
;y dd 0
;xt dd 0
;yt dd 0
;wz dd 0
;radius dd 0
;start dd 0
;pi180 dd 0.017453292519943296
;l8 dd 8.0
;fpuout dd 0
;l40000 dd 40000.0
;l256 dd 256.0
;l190 dd 190.0
;l100 dd 100.0
;l1000 dd 1000.0
;l1_8 dd 0.125
;lA dd 0
;lB dd 0
;lC dd 0
;lD dd 0
;llE dd 0
