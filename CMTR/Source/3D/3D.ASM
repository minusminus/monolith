.386
code32 segment para public use32 'code'
assume cs:code32,ds:code32,es:code32

include c:\tasm\tools\eos\303\resource\eos.inc


debugface=0

;includy
include vesa.asm
include sin64k.tbl
include bitsort.inc
;include makemat.inc
include matrix.inc
include persp.inc
include rot.inc
include vis.inc
include sumujz.inc
include normals.inc
include wersory.inc
include obgen.inc

include punkty.inc

;zmienne
vesabuf dd ?
bufor dd ?
dz: dd 1024*2+1 dup(?)
dzieltbl dd ?
fpu1 dd ?
envm dd ?
phm dd ?
magic dd 0,42380000h
fastdivtbl dd ?
fpuout dd ?,?
l64k dd 1.0
c3c1 dd ?
c3s1 dd ?
s3s1 dd ?
s3c1 dd ?
lm1 dd -1.0
alfa dd 0
beta dd 0
gamma dd 0
verttbl dd offset brvertexy
facetbl dd offset trojkaty
facecount dd 20*6
wsp3d dd offset vertexy
vertexcount dd 6*16
l256 dd 256.0
l128 dd 128.0
l05 dd 0.5
l1 dd 1.0
l3204 dd 320.0

;obiekt
include obfac.inc	;oryginal
brvertexy:
db 6*16*4*6 dup(?)	;przed obrotami
vertexy:
db 6*16*4*9 dup(?)	;po obrotach
trojkaty:
db 6*20*4*8 dup(?)	;face'y





;do procedury sortujacej
sumaZtbl dd ?
pomsumaZtbl dd ?
ujnum dd ?
dodnum dd ?
facevis dd ?
offseteldod label dword
dd 16 dup(?)
offseteluj label dword
dd 16 dup(?)

;dla perspektywy
distance dd 450.0
korx dd 160.0
kory dd 100.0

;macierz obrotu
macierz: dd 9 dup(?)



;public i extrn
extrn initenvy : near
extrn envy : near

public bufor
public vesabuf
public magic
public envm
public phm
public fastdivtbl


;pliki z texturami
gifplik: db 'tunel.raw',0	;tekstura
phongplik: db 'phong.raw',0	;phongmap


;pliki debuggingu
debugplik: db 'debug.mem',0


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




;ladowanie textur itd
mov ah,allocate_memory	;alokuj bufor
mov edx,320*200*4*2
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



;alokacja tablic do sortowania
mov ah,allocate_memory
mov edx,6*20*4*4*2
int_eos
mov sumaZtbl,edx
add edx,6*20*4*4
mov pomsumaZtbl,edx



;debug
if debugface
mov eax,vesabuf
mov bufor,eax
endif

;tablica do szybkiego dzielenia
call dztbl


;generacja obiektu
call objectgen

;liczenie normalsow i wersorow
;call debug
mov esi,facetbl
mov ecx,facecount
call normals
call wersory	;liczy normalsy w pktach obiektu


;call writedebug


;init wypelniacza
call initenvy

mov alfa,0
mov beta,270
mov gamma,0


;*******************************************************************
;*******************************************************************
;rysowanie obiektu

englup:
;zerowanie zmiennych
mov facevis,0
mov dodnum,0
mov ujnum,0
;obrot obiektu i swiatla

;call debug

;mov esi,sintbl
;mov eax,alfa
;mov ebx,beta
;mov ecx,gamma
;mov edi,offset macierz
;call makerotmatrix
mov ebx,offset macierz
mov edx,sintbl
mov ebp,offset alfa
call makemat

mov esi,verttbl 	  ;tablica pktow obiektu [oryginalna]
mov edi,wsp3d	     ;tablica pktow po obrocie -> do tych pktow sa adresy
		     ;w face'ach
mov ebx,offset macierz	       ;macierz obrotu
mov ecx,vertexcount	;licznik
call rotate

mov esi,verttbl
mov edi,wsp3d
mov ebx,offset macierz
mov ecx,vertexcount
call rotateback



mov esi,wsp3d
mov ecx,vertexcount
rbblopp:
fld dword ptr[esi+20]
fmul dword ptr[l05]
;fadd dword ptr[l1]
fadd dword ptr[l128]
fstp dword ptr[esi+20]
fld dword ptr[esi+24]
fmul dword ptr[l05]
;fadd dword ptr[l1]
fadd dword ptr[l128]
fstp dword ptr[esi+24]
add esi,4*9
dec ecx
jnz rbblopp


;wyrzucenie facow ktore sa tylem
mov esi,facetbl 	;poczatek tablicy face'ow
;add esi,2*20*4*8
mov ecx,facecount
mov edi,sumaZtbl
call visible

mov ecx,facevis
cmp ecx,0
jle nodraw
;sumowanie Z
;call debug
mov esi,sumaZtbl
mov ecx,facevis
call sumujZ


;call debug
;sortowanie sum Z
mov edi,sumaZtbl
mov esi,pomsumaZtbl
call bitsort


;perspektywa dla posortowanych facow
mov esi,sumaZtbl	;adresy face'ow do policzenia perspektywy
mov ecx,facevis
call perspective

;czyszczenie bufora
call clrbuf

;;rysowanie facow
mov edx,sumaZtbl
mov ecx,facevis
;cmp ecx,0
;jle nodraw
lea edx,[edx+4*ecx-4]
;call debug
drawlup:
mov esi,[edx]	    ;adres faca
mov eax,[esi+12]
pushad
if debugface
wddd:
mov ah,01h
int 16h
jz wddd
mov ah,0
int 16h
cmp al,'w'
jne dontwrite
mov ebp,esi
call writefaceinfo
dontwrite:
call envy
;call punkty
else
call envy
;call punkty
endif
popad
sub edx,4
dec ecx
jnz drawlup

;call writedebug


nodraw:
call ramka
call drop
call katy
;call waitkey
mov ah,01h
int 16h
jz englup
mov ah,00h
int 16h
cmp al,'q'
jne koncowka
;cmp al,'w'
;jne kkk1
;mov eax,alfa
;add eax,1
;cmp eax,360
;jb kkoka
;xor eax,eax
;kkoka:
;mov alfa,eax
;kkk1:
;cmp al,'s'
;jne kkk2
;mov eax,beta
;add eax,1
;cmp eax,360
;jb kkokb
;xor eax,eax
;kkokb:
;mov beta,eax
;kkk2:
;cmp al,'x'
;jne kkk3
;mov eax,gamma
;add eax,1
;cmp eax,360
;jb kkokg
;xor eax,eax
;kkokg:
;mov gamma,eax
;kkk3:
;jmp englup


;*******************************************************************
;*******************************************************************







koncowka:

mov ax,0003h
int 10h
koniec:
mov ax,4c00h
int 21h



;blad vesy
Blad	    db ' Vesa error ! ',13,10,'$'

;talbica szybkiego dzielenia
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


writedebug proc
mov ah,write_external_file
mov edx,offset debugplik
mov ecx,9600
mov esi,offset brvertexy
int_eos
mov ax,0003h
int 10h
mov ax,4c00h
int 21h
ret
endp


katy proc
mov eax,alfa
add eax,1
cmp eax,360
jb oka
xor eax,eax
oka:
mov alfa,eax
mov eax,beta
add eax,0
cmp eax,360
jb okb
xor eax,eax
okb:
mov beta,eax
mov eax,gamma
add eax,0
cmp eax,360
jb okg
xor eax,eax
okg:
mov gamma,eax
ret
endp


waitkey proc
wk:
mov ah,01h
int 16h
jz wk
mov ah,00h
int 16h
ret
endp

;zapisuje info face'a na dysku [debugging]
;we:ebp - adres face'a
writefaceinfo proc
pushad
mov esi,ebp	   ;przepisz face'a dane
mov edi,offset fface
mov ecx,8
cld
rep movsd
mov esi,[ebp+0] ;1 wierzcholek
mov edi,offset fvert
mov ecx,9
cld
rep movsd
add edi,2*4
mov esi,[ebp+4] ;2w
mov ecx,9
cld
rep movsd
add edi,2*4
mov esi,[ebp+8] ;3w
mov ecx,9
cld
rep movsd
mov ah,write_external_file
mov ecx,4*8+3*4*11
mov edx,offset fdbgname
mov esi,offset fface
int_eos
popad
mov ax,0003h
int 10h
mov ax,4c00h
int 21h
ret

fface:
dd 8 dup(0)
fvert:
dd 11*3 dup(0)
fdbgname:
db 'face.dbg',0
endp


code32 ends
end