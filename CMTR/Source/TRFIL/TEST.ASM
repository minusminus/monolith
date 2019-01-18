.386
jumps
code32 segment para public use32 'code'
assume cs:code32,ds:code32,es:code32
include c:\tasm\tools\eos\303\resource\eos.inc


include vesa.asm


extrn initenvy : near
extrn envy : near

public bufor
public vesabuf
public magic
public envm
public phm
public fastdivtbl

bufor dd 0
vesabuf dd 0
envm dd 0
phm dd 0
magic dd 0,42380000h
fastdivtbl dd 0
l64k dd 1.0
fpu1 dd 0
dz: dd 1024*2+1 dup(0)


face:
dd offset p1
dd offset p2
dd offset p3
p1:
dd ? ;x
dd ? ;y
dd ? ;z
dd 144.9235 ;x2d
dd 175.0000 ;y2d
dd -104.5;nx
dd -104.5;ny
dd -104.5;nz
p2:
dd ? ;x
dd ? ;y
dd ? ;z
dd 175.1 ;x2d
dd 145.0 ;y2d
dd -85.3 ;nx
dd -85.3 ;ny
dd -85.3 ;nz
p3:
dd ? ;x
dd ? ;y
dd ? ;z
dd 144.9 ;x2d
dd 145.0 ;y2d
dd -42.6 ;nx
dd -42.6 ;ny
dd -42.6 ;nz
face2:
dd offset pp1
dd offset pp2
dd offset pp3
pp1:
dd ? ;x
dd ? ;y
dd ? ;z
dd 144.9 ;x2d
dd 175.0 ;y2d
dd -104.5;nx
dd -104.5;ny
dd -104.5;nz
pp2:
dd ? ;x
dd ? ;y
dd ? ;z
dd 175.1 ;x2d
dd 175.0 ;y2d
dd -52.3 ;nx
dd -52.3 ;ny
dd -52.3 ;nz
pp3:
dd ? ;x
dd ? ;y
dd ? ;z
dd 175.1;x2d
dd 145.0 ;y2d
dd -85.3 ;nx
dd -85.3 ;ny
dd -85.3 ;nz

gifplik: db 'tunel.raw',0	;tekstura
phongplik: db 'phong.raw',0	;phongmap

setborder macro r,g,b
	mov dx,3c8h
	mov al,0
	out dx,al
	inc dx
	mov al,r
	out dx,al
	mov al,g
	out dx,al
	mov al,b
	out dx,al
	endm

start32:
finit
;vesa init
	    mov ebx,1b9h	    ; numer trybu 320x200x32bpp
	    mov edx,1		    ; z linearem
	    call vesa_set_mode_
	    jnc mode_ok
	    mov edx,offset Blad
	    mov ah,9
	    int 21h
	    jmp koniec
mode_ok:
	    mov edx,[_vesa_screen_addy]       ; wez adres ekranu i ...
	    mov [_vesa_screen_bufor],edx      ; ... podstaw jako bufor
	    mov ecx,vesa_screen_size	      ; rozmiar ekranu
	    mov edx,_vesa_screen_bufor
	    mov vesabuf,edx

;call debug
mov ah,allocate_memory	;alokuj bufor
mov edx,320*200*4
int_eos
mov bufor,edx

mov ah,load_external_file
mov edx,offset gifplik
int_eos
mov envm,eax

mov ah,load_external_file
mov edx,offset phongplik
int_eos
mov phm,eax



;call debug
call initenvy
call dztbl

;jmp after
;tunellup:
call clrbuf
;call drop
mov esi,offset face
call debug
call envy
mov esi,offset face2
;call debug
call envy
;after:
call ramka
call drop
;call waitkey


keylup:
;setborder 0,255,0
mov ah,01h
int 16h
jz keylup
;jz tunellup
mov ah,00h
int 16h
;cmp al,'q'
;je exit
;call negacja
;jmp tunellup

exit:
mov ah,deallocate_memory
int_eos
koniec:
mov ax,0003h
int 10h

koniec2:
mov ax,4c00h
int 21h

;do bledu vesy
Blad	    db ' Vesa error ! ',13,10,'$'

drop proc
     mov esi,bufor
     mov edi,vesabuf
     mov ecx,64000
     cld
     rep movsd
     ret
drop endp

Ramka	PROC
	mov dx,3dah
ram1:	in al,dx      ;sprawdz 3 bit portu
	test al,8
	jnz ram1
ram2:	in al,dx     ;ponownie sprawdz
	test al,8
	jz ram2
	ret
Ramka	ENDP

clrbuf proc
       xor eax,eax
       mov edi,bufor
       mov ecx,64000
       cld
       rep stosd
       ret
clrbuf endp

waitkey proc
mov ah,01h
int 16h
jz waitkey
ret
endp


dztbl proc
mov edi,offset dz
mov ecx,-1024
dzlup:
mov fpu1,ecx
cmp ecx,0
jne okmian
inc dword ptr[fpu1]
okmian:
fld dword ptr[l64k]
fild dword ptr[fpu1]
fdivp st(1),st
fstp dword ptr[edi]
add edi,4
inc ecx
cmp ecx,1025
jl dzlup
mov edi,offset dz	;na srodek
add edi,1024*4
mov fastdivtbl,edi
ret
endp


code32 ends
end