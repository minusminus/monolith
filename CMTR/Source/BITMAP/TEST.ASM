.386
code32 segment page public use32 'code'
assume cs:code32,ds:code32,es:code32

include c:\tasm\tools\eos\303\resource\eos.inc


speed=0
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


include vesa.asm
include bitm.inc
include gen.inc


include sin64k.tbl

vesabuf dd ?
bufor dd ?
text dd ?
wezly dd ?  ;tablica z wartosciami do interpolacji

tex1: db 'tex.raw',0

start32:
finit
if speed
mov ax,0013h
int 10h
else
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
endif

;ladowanie textur itd
mov ah,allocate_memory	;alokuj bufor
mov edx,320*200*4
int_eos
mov bufor,edx

mov ah,allocate_memory
mov edx,41*26*8        ;41x26 x,y
int_eos
mov wezly,edx

mov ah,load_external_file
mov edx,offset tex1
int_eos
mov text,eax

mov eax,text
call initbitmap

;call debug
drawlup:
if speed
call ramka
setborder 0,0,63h
call generuj
call drawbitmap
;call ramka
;call drop
setborder 0,63h,0
else
call generuj
call drawbitmap
call ramka
call drop
endif

inc dword ptr[start]
inc dword ptr[start]
mov ah,01h
int 16h
jz drawlup
mov ah,0
int 16h




mov ax,0003h
int 10h
koniec:
mov ax,4c00h
int 21h

blad: db 'vesa error',13,10,'$'


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


code32 ends
end