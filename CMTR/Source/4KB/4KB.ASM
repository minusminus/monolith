.586
code segment use16 public
assume cs:code,ds:code,es:code

include upmem.inc
vertexcount equ 6*16
facecount   equ 6*20
; segmenty - ds=cs
;	     es=0

org 100h
start:
;ฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤ Initial tests ฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤ
	 cld
	 mov	 ax,4f00h
	 int	 2fh	     ; look for himem.sys
	 cmp	 al,80h
	 je	 error_end
	 mov	 eax,cr0
	 test	 al,1	     ; already in virtual mode ?
	 jnz	 error_end
;ฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤ VESA stuff ฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤ
	 mov	 ax,4f01h    ; get mode info
	 mov	 cx,10fh      ;320x200x24bit
	 mov	 di,offset vesa_buffer
	 int	 10h
	 mov	 ax,4f02h
	 mov	 bx,0410fh    ;clear video mem and set with linear bufer
	 int	 10h
	 test	 ah,1
	 jnz	 error_end
;	  xor	  eax,eax
;	  mov	  ax,cs
;	  shl	  eax,4
;	  mov	  ebx,dword ptr [vesa_buffer+28h]
;	  sub	  ebx,eax
;	  mov	  [linear_addy],ebx
;ฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤ Interrupt shit ฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤ
;	  mov	  ax,3508h
;	  int	  21h	      ;get old int8h vector
;	  mov	  word ptr [oldseg8h],es
;	  mov	  word ptr [oldoff8h],bx
;	  mov	  dx,offset newint8h
;	  mov	  ah,25h
;	  int	  21h	      ;set new int8h vector
;	  mov	  al,36h
;	  out	  43h,al
;	  mov	  ax,17039
 ;	  out	  40h,al
 ;	  mov	  al,ah
 ;	  out	  40h,al
	 call	 adlib_init
	 mov	 ax,3509h
	 int	 21h	     ;get old int9h vector
	 mov	 word ptr [oldseg9h],es
	 mov	 word ptr [oldoff9h],bx
	 mov	 dx,offset keyboard_end
	 mov	 ah,25h
	 int	 21h	     ;set new int9h vector
;อออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออ
	 xor	 ebp,ebp
	 mov	 ax,1130h
	 mov	 bh,3
	 int	 10h	     ;es:bp - adres fontow
	 mov	 edi,tytul
	 mov	 si,offset txttytul
	 call	 writestring
	 xor	 ax,ax
	 mov	 es,ax
	 fninit
;generator tablicy sinusow
	 fldz
	 mov	 si,offset sintbl
	 mov	 cx,360+90
singenloop:
	 fld	 st(0)
	 fsin
	 fstp	 dword ptr [si]
	 fadd	 dword ptr [pi180]
	 add	 si,4
	 loop	 singenloop
	 fstp	 st(0)
	 call	 CalculateSinCos
	 call	 calculateusin


; generacja textury na tunel
	 call	 clear_temp
	 mov	 edi,temp_seg1
	 mov	 al,128
	 mov	 si, offset PlasmaPoint4
	 call	 MakePlasma
	 mov	 edi,temp_seg2
	 mov	 al, 12
	 mov	 si, offset PlasmaPoint2
	 call	 MakePlasma
	 mov	 edi,textunel
	 mov	 esi,temp_seg1
	 mov	 dl,3
	 call	 MakeTrueTexture
; textura 3
	 call clear_temp
	mov   edi,temp_seg1
	mov   al,100
	mov   si, offset PlasmaPoint2
	call  MakePlasma

	mov   edi,temp_seg3
	mov   al, 180
	mov   si, offset PlasmaPoint4
	call  MakePlasma


	mov   edi,tex3
	mov   esi,temp_seg1
	mov   dl,3
;	 mov   edx,0008f03h
	call  MakeTrueTexture
; textury do drugiej czesci
	 mov	 edi,tex1
	 mov	 eax,0ffff00h	    ;\na obiekt
	 mov	 edx,0ffa400h	    ;/
	 call	 szachownica
	 mov	 edi,tex1n
	 mov	 eax,0h
	 mov	 edx,0ff9400h
	 call	 szachownica
;generator obiektu
;	  call	  objectgen
;	  mov	  si,offset facetbl
;	  mov	  cx,facecount
;	  call	  normals
;	  call	  wersory    ;liczy normalsy w pktach obiektu
	 call	 init_3d
; generowanie phongmapy
include phgen.inc
; rozszerzenie tablicy phongmapy
	 mov	 esi,phmap	 ;\
	 mov	 edi,phmapext	 ; rozszerza phongmape dla szybszego mmx'a
	 mov	 ecx,256*256*4
mpc:	 movzx	 eax,byte ptr [esi]
	 shl	 eax,1
	 sub	 eax,256
	 mov	 [edi],ax
	 inc	 esi
	 add	 edi,2
	 dec	 ecx
	 jnz	 mpc
; generowanie tablicy dla bumpa
include bumptext.inc
; generowanie tablicy dla tunelu
include tungen.inc
;อออออออออออออออออออออออออออ Main code อออออออออออออออออออออออออออออออออ
;include part1.asm
include part2.asm

lup:
	 jmp lup
;	  jmp normal_end
;อออออออออออออออออออออออออออออออออออออ Exit code อออออออออออออออออออออออออออ
keyboard_end:
	 in	 al,60h 	 ; load key scancode
	 mov	 al,20h
	 out	 20h,al
	 push	 cs
	 pop	 ds
normal_end:
	 mov	 dx,word ptr [oldoff9h]
	 mov	 ax,word ptr [oldseg9h]
	 mov	 ds,ax
	 mov	 ax,2509h
	 int	 21h	     ;set old int9h vector
	 push	 cs
	 pop	 ds
	 call	 adlib_close
;	  mov	  al,36h
;	  out	  40h,al
;	  mov	  al,255
;	  out	  40h,al
;	  out	  40h,al
;	  mov	  dx,word ptr [oldoff8h]
;	  mov	  ax,word ptr [oldseg8h]
;	  mov	  ds,ax
;	  mov	  ax,2508h
;	  int	  21h	      ;set old int8h vector
	 mov	 ax,3
	 int	 10h
error_end:
	 mov	 ah,4ch
	 int	 21h

clear_temp:
	 mov	 edi,temp_seg1
	 mov	 cx,49152
memset:
	 ; edi - dest
	 ; cx - size in dwords
	 xor	 eax,eax
memset_loop:
	 mov	 dword ptr [edi],eax
	 add	 edi,4
	 loop	 memset_loop
	 ret

show_screen:
	 mov	 eax,dword ptr [vesa_buffer+28h]
	 mov	 esi,screen_buffer

;	  mov dx,3dah
;ram1:	  in al,dx	;sprawdz 3 bit portu
;	  test al,8
;	  jnz ram1
;ram2:	  in al,dx     ;ponownie sprawdz
;	  test al,8
;	  jz ram2

	 mov	 bp,64000
show_24_bpp_loop:
	 mov	 edx,dword ptr [esi]
	 add	 esi,4
	 mov	 dword ptr es:[eax],edx
	 add	 eax,3
	 dec	 bp
	 jnz	 show_24_bpp_loop
	 ret
;-----------------------
include adlib.inc
include bumpproc.inc
include texgen.inc
include fonty.inc
include bitm.inc
include kula.inc
include gen.inc
include render.inc
;include timer.inc
;-----------------------
include lomem.inc

code ends
end start

