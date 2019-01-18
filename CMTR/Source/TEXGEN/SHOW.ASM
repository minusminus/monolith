.586
code32 segment para public use32 'code'
assume cs:code32,ds:code32,es:code32

include c:\tasm\tools\eos\303\resource\eos.inc


;save
plik: db 'tex.raw',0


;vesa stuff
include vesa.asm
vesabuf dd ?
phbuf dd ?
fpuout dd ?
xs dd 128.0
ys dd 128.0
rr dd 16384.0


blad: db 'novesa','$'


include phgen.inc



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


;mov ah,load_external_file
;mov edx,offset plik
;int_eos
;mov esi,eax


;jmp nophong
;generacja phonga
mov ah,allocate_memory
mov edx,265*256*4
int_eos
mov phbuf,edx
call phgen

mov ah,write_external_file
mov edx,offset plik
mov ecx,256*256*4
mov esi,phbuf
int_eos

nophong:

;wyswietlenie
mov edi,vesabuf
mov esi,phbuf
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


mov ax,0003h
int 10h
koniec:
mov ax,4c00h
int 21h



code32 ends
end


