.586
code32 segment para public use32 'code'
assume cs:code32,ds:code32,es:code32

include c:\tasm\tools\eos\303\resource\eos.inc


;zmienne i takie tam duperele
include memdata.inc
;generator
include txtg_dat.asm
include txtgen.asm



;save
plik: db 'tex.raw',0


;vesa stuff
include vesa.asm
vesabuf dd ?


blad: db 'novesa','$'

start32:
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



;przydzial pamieci
mov ah,allocate_memory
mov edx,16000000
int_eos
mov ebx,edx
mov edi,edx
xor eax,eax
mov ecx,16000000/4
cld
rep stosd
include givemem.inc


mov edi,vesabuf
mov eax,-1
mov ecx,320*20
cld
rep stosd

;licz sincos
call calculatesincos
call calculateusin


;generacja textury
;include mtxt00.asm
include 2n.tex


;wyswietlenie
mov edi,vesabuf
mov esi,txt0
mov edx,200
pl:
mov ecx,256
cld
rep movsd
add edi,(320-256)*4
dec edx
jnz pl

kwait:
mov ah,1
int 16h
jz kwait
mov ah,0
int 16h
cmp al,'y'
jne dontsave
mov ah,write_external_file
mov edx,offset plik
mov ecx,256*256*4
mov esi,txt0
int_eos

dontsave:


mov ax,0003h
int 10h
koniec:
mov ax,4c00h
int 21h



code32 ends
end


