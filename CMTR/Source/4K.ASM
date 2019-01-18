.586P
.587
code segment use16 public
assume cs:code,ds:code,es:code
; ds == es == cs
; fs = 0

org 100h

start:
;jmp here
;      mov ax,cs
;      mov ds,ax
;      mov es,ax
      push cs cs
      pop ds es
      xor ax,ax
      mov fs,ax
      mov ax,4f00h
      int 2fh	      ;is XMS present
      cmp al,80h
      jne okxms
      mov dx,offset err1
      jmp errprnt
okxms:
      mov eax,cr0
      test al,1       ;are we in V86
      jz nov86
      mov dx,offset err3
      jmp errprnt
nov86:

;jmp okvesa
      mov ax,4f01h
      mov cx,1b9h     ;320x200x32bit
;      mov cx,10fh
      mov di,offset verttbl
      int 10h	    ;mode info block
      mov ax,4f02h
      mov bx,041b9h   ;clear video mem and set with linear bufer
;      mov bx,410fh
      int 10h
      test ah,1
      jz okvesa
      mov dx,offset err2
      jmp errprnt


okvesa:
      mov eax,dword ptr[verttbl+28h]
      mov vesabufor,eax
      mov ax,3508h
      int 21h	      ;get old int8h vector
      mov word ptr [oldseg8h],es
      mov word ptr [oldoff8h],bx
      mov dx,offset newint8h
      mov ax,2508h
      int 21h	      ;set new int8h vector
      xor ebp,ebp
      mov ax,1130h
      mov bh,3
      int 10h	      ;es:bp - adres fontow

;      finit
      fninit

;generacja napisow
      mov byte ptr [c1632],1
      mov edi,tytul
      mov si,offset txttytul
      call writestring
      mov edi,endtxt
      mov si,offset txtendtxt
      call writestring
      mov byte ptr [c1632],0
;      mov bx,offset string_table
      mov edi,c1
      mov bx,15
      mov si,offset txtc1
gen_str_loop:
;      mov edi,dword ptr [bx]
;      mov si,word ptr [bx+4]
      push bx edi si
      call writestring
      pop si edi bx
      add edi,stxt16
search0:
      inc si
      cmp byte ptr[si-1],0
      jne search0
;      add bx,6
;      cmp bx,offset end_string_table
;      jb gen_str_loop
      dec bx
      jnz gen_str_loop

      push cs
      pop es
;generator tablicy sinusow
;      mov esi,sintbl
;      mov cx,360+90
;      xor bx,bx
;singenloop:
;      mov word ptr[fpuout],bx
;      fild word ptr[fpuout]
;      fmul dword ptr[pi180]
;      fsin
;      fstp dword ptr[esi]
;      add esi,4
;      inc bx
;      dec cx
;      jnz singenloop
;generator fastdivtbl
;      mov edi,fdt
;      mov cx,-1024
;dzlup:
;      mov word ptr [fpuout],cx
;      cmp cx,0
;      jne okmian
;      inc word ptr[fpuout]
;okmian:
;      fld1
;      fidiv dword ptr[fpuout]
;      fstp dword ptr[edi]
;      add edi,4
;      inc cx
;      cmp cx,1025
;      jl dzlup
;generacja textur	DZIALA [trzeba rozmiar zoptymalizowac]
;      call calculatesincos
;======================================
	 mov	 di, offset _costable
	 mov	 si, offset _sintable
	 mov	 ecx,256	     ; ile pozycji w tablicy
pet_sin:
	 mov	 dword ptr [fpuout],256
	 sub	 [fpuout], ecx
	 fldpi				 ; zaladuj PI na stos
	 fimul	 dword ptr [fpuout]		     ; x * PI
;	  mov	  dword ptr [fpuout],128
;	  fidiv   dword ptr [fpuout]		      ; ( x * PI ) / (NUMBER / 2)
	 fdiv dword ptr[l128]
	 fsincos			 ; sin( ( x * PI ) / ( NUMBER / 2 ) )
	 fimul	 dword ptr [MULT]		   ; MULT * sin( (x*PI) / (NUMBER / 2))
;	  frndint			  ; zaokraglij do liczby calkowitej
	 fistp dword ptr[di]
	 add	 di, 4			;zapamietaj cosinus w tablicy
	 fimul	 dword ptr [MULT]		   ; MULT * sin( (x*PI) / (NUMBER / 2))
;	  frndint			  ; zaokraglij do liczby calkowitej
	 fistp dword ptr[si]
	 add	 si, 4			;zapamietaj sinus w tablicy
	 loop	 pet_sin
;======================================

;      call calculateusin
;======================================
	 mov	 si, offset _sintable
	 mov	 di, offset usintbl
	 mov	 cx,256
	 push	 si
cus_pet:
	 call	 processSin
	 call	 endSIN
	 jnz	 cus_pet
	 pop	 si

	 push	 si
	 mov	 di, offset usintbl2
	 mov	 ch,1
cus_pet2:
	 call	 processSIN
	 or	 al,cl
	 call	 endSIN
	 jnz	 cus_pet2
	 pop	 si
	 mov	 di,offset usintbl3
	 mov	 ch,1
cus_pet3:
	 call	 processSIN
	 xor	 al,cl
	 call	 endSIN
	 jnz	 cus_pet3
;======================================

      call cleantemp
include 2.tex	   ;textura na tunel
      call cleantemp
include 3.tex	   ;na koncowa kule
      call cleantemp
include 5n.tex	    ;szachownica
      call cleantemp
include 4.tex	   ;na efekt bitmapowy
include phgen.inc   ;generator phongmapy
      mov esi,phmap	  ;\
      mov edi,phmapext	  ; rozszerza phongmape dla szybszego mmx'a
;      call expandtexture  ;/
;======================================
mov ecx,256*256*4
mpc:
movzx eax,byte ptr [esi]
shl eax,1
sub eax,256
mov [edi],ax
inc esi
add edi,2
dec ecx
jnz mpc
;======================================


;xor ax,ax
;mov ds,ax
include tungen.inc	;generator tablicy tunelu
      call bumptexture	      ;bampuje texture


;generator obiektu
;      call objectgen
;======================================
mov di,offset verttbl
mov si,offset wsp3d
mov bx,offset cubepoints
mov cx,3*16
Acploop:
mov bp,3
AploopG:
movsx ax,byte ptr[bx]
mov word ptr[fpuout],ax
fild word ptr[fpuout]
inc bx
dec bp
jnz AploopG

mov bp,8
AploopC:
fst dword ptr[di+bp]
fst dword ptr[si+bp]
fchs
fst dword ptr[di+bp+4*6*3*16]
fstp dword ptr[si+bp+4*9*3*16]
sub bp,4
jns AploopC
add di,4*6
add si,4*9
dec cx
jnz Acploop

;generuje face'y
mov di,offset facetbl
xor ax,ax
mov bp,6
Afacegenml:
mov si,offset mainface
mov dx,20
;call expandface	 ;facetbl przesuniete odpowiednio w procedurze
;========================
expl:
xor ecx,ecx
movzx cx,byte ptr[si]
dec cx
add cx,ax
imul cx,9*4
add cx,offset wsp3d
mov [di+0],ecx
movzx cx,byte ptr[si+1]
dec cx
add cx,ax
imul cx,9*4
add cx,offset wsp3d
mov [di+4],ecx
movzx cx,byte ptr[si+2]
dec cx
add cx,ax
imul cx,9*4
add cx,offset wsp3d
mov [di+8],ecx
add si,3
add di,8*4
dec dx
jnz expl
;========================

mov si,offset mainface
mov dx,20
add ax,16      ;nastepne pkty
dec bp
jnz Afacegenml
;======================================



mov si,offset facetbl
mov cx,facecount
;call normals
include normals2.inc
;call wersory	 ;liczy normalsy w pktach obiektu
include wersory.inc



;dzialajaca czec 1
include part1.asm	;czesc1 -> tunel bumpowany

include part2.asm	;czesc2 -> obiekt + tlo + creditsy

include part3.asm	;czesc3

include part4.asm	;czesc4

;koniec juz
koniecxxx:
mov dx,word ptr [oldoff8h]
mov ax,word ptr [oldseg8h]
mov ds,ax
mov ax,2508h
int 21h 	;set old int8h vector

push cs
pop ds
mov dx,offset ok     ;everything is ok
errprnt:	;error print
mov ax,0003h
int 10h 	;textmode
mov ah,9
int 21h
mov ah,4ch
int 21h

err1:
db 'NO XMS',10,'$'
err2:
db 'VESA ERROR',10,'$'
err3:
db 'V86',10,'$'
ok:
db 'OK',10,'$'

;procki
newint8h proc
push ax
push ds
push cs
pop ds
inc word ptr [counter]
dec byte ptr [y1adder]
dec byte ptr [x1adder]
dec byte ptr [x1adder]
inc byte ptr [y2adder]
inc byte ptr [x2adder]
inc byte ptr [x2adder]
add dword ptr [startN],4

;flash
;inc word ptr [fontflash]
mov ax,word ptr[fontflash]
test byte ptr[flashdir],1
jz zmniejsz
inc ax
inc ax
cmp ax,255
jle wstawflash
mov ax,255
jmp wstawflash
zmniejsz:
dec ax
dec ax
cmp ax,0
jge wstawflash
xor ax,ax
wstawflash:
mov word ptr[fontflash],ax

;katy obrotow
mov ax,word ptr [alfa]
add ax,2*2
cmp ax,360
jb oka
xor ax,ax
oka:
mov word ptr [alfa],ax
;mov ax,word ptr [beta]
;add ax,2*2
;cmp ax,360
;jb okb
;xor ax,ax
;okb:
mov word ptr [beta],ax
mov ax,word ptr [gamma]
add ax,2
cmp ax,360
jb okg
xor ax,ax
okg:
mov word ptr [gamma],ax

mov al,20h
out 20h,al
pop ds
pop ax
iret
endp


;dane
;include data.inc

;fonty
include fonty.inc
;generator textur
include texgen.asm
;generator bumpmapy
include bumptex.inc
;generator obiektu
;include obgen.inc
;generator efektow bitmapowych w tle
include gen.inc
;procki do generacji efektow
include kula.inc
include greetsy.inc
include greetsy2.inc
;rysujaca tlo
include bitm.inc
;adlib player
;include adlib.inc
;3D
;include bitsort.inc
;include bubble.inc
include matrix.inc
;include normals.inc
;include persp.inc
include rot.inc
;include sumujz.inc
;include vis.inc
;include wersory.inc
;include env.asm
include faceenv.asm
include do3d.asm	;renderer
;tunel bumpowany
include bumpyt.inc

;czysci bufor dla generatora textur
cleantemp proc
mov edi,temp_seg1
xor eax,eax
mov bl,3
clolup:
mov cx,256*256/4
clilup:
mov [edi],eax
add edi,4
dec cx
jnz clilup
dec bl
jnz clolup
ret
endp

;expander phongmapy z dd na dq
;expandtexture proc
;;mov esi,phmap
;;mov edi,tpb
;mov ecx,256*256*4
;mpc:
;;xor eax,eax
;movzx eax,byte ptr [esi]
;shl eax,1
;sub eax,256
;mov [edi],ax
;inc esi
;add edi,2
;dec ecx
;jnz mpc
;ret
;endp

;zrzucanie ekranu
drop proc
     mov esi,bufor
     mov edi,dword ptr [vesabufor]
     mov cx,64000
	mov dx,3dah
ram1:	in al,dx      ;sprawdz 3 bit portu
	test al,8
	jnz ram1
ram2:	in al,dx     ;ponownie sprawdz
	test al,8
	jz ram2
;     cld
;     rep movsd
push es
xor ax,ax
mov es,ax
droplup:
	 mov eax,[esi]
	 add esi,4
	 mov es:[edi],eax
	 add edi,4
	 dec cx
	 jnz droplup
;show_24_bpp_loop:
;	  mov	  eax,dword ptr [esi]
;	  add	  esi,4
;	  mov	  dword ptr es:[edi],eax
;	  add	  edi,3
;	  dec	  cx
;	  jnz	  show_24_bpp_loop
pop es
     ret
drop endp

;robi kolor
;bl - numer stringa w tablicy
;bh = 0
makefontcolor proc
xor ah,ah
mov al,byte ptr[flashcol]
push ax
shl eax,16
pop ax
mov dword ptr fontcol[0],eax
mov dword ptr fontcol[4],eax
ret
endp


;wyjscie po nacisnieciu klawisza



;dane
include data.inc

;rozklad danych w pamieci
include mem.inc

code ends


end start
