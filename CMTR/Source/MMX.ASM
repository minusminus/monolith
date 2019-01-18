.586
code segment use16 public
assume cs:code,ds:code,es:code

org 100h

;public printfonttbl
public bumpytunel
;public envylinedraw
;public envylinedrawE
;public stalenx
;public staleny

extrn y1adder:byte
extrn y2adder:byte
extrn x1adder:byte
extrn x2adder:byte
;extrn fontcol:qword


include mem.inc



;;wyswietla na ekranie string z bufora 320x32 MMX
;;edi - adres w buforze ekranu
;;esi - adres napisu do wyswietlenia
;;syf dd 5555h
;printfonttbl proc
;      push es
;      xor ax,ax
;;	mov es,ax
;      movq mm1,qword ptr ds:[fontcol] ;kolor fontu juz przerobiony pod mmx'a
;      mov cx,320*32
;pftlup:
;      cmp byte ptr ds:[esi],0
;      je nextpoint
;;	punpcklbw mm0,dword ptr es:[edi]
;;	psrlw mm0,8
;;	paddusw mm0,mm1
;;	psrlw mm0,1
;;	packuswb mm3,mm0
;;	psrlq mm3,32
;      punpcklbw mm0,dword ptr [edi]
;      psrlw mm0,8
;      paddusw mm0,mm1
;      packuswb mm3,mm0
;      psrlq mm3,32
;      movd dword ptr [edi],mm3
;;	movd dword ptr ds:[edi],mm1
;
;nextpoint:
;      inc esi
;      add edi,4
;      dec cx
;      jnz pftlup
;
;      emms
;      pop es
;      retn
;printfonttbl endp







;rysuje bumpowany tunel
bumpytunel proc
mov edi,bufor
mov esi,tablicexy	;tablica tunelu
mov dh,[y1adder]
mov dl,[x1adder]
mov bl,[x2adder]
mov bh,[y2adder]
mov bp,320*200	       ;ilosc pktow ekranu

movq mm5,qword ptr [m1]

btloop:
mov eax,[esi]		;adres texturki w tunelu
mov ecx,[esi]		;adres do bumpmapy
add ah,dh
add ch,bh
add al,dl
add cl,bl
texo: punpcklbw mm2,dword ptr [4*ecx+textunel]
bumpo: mov ecx,[4*ecx+bumpmap]	     ;wez przesuniecie z bumpmapy
add ch,ah
add cl,al
;phoo: movq mm1,qword ptr ds:[8*ecx+phmapext]	       ;wez kolor z phongmapy

;dodanie koloru [mmx version]
psrlw mm2,8
;paddw mm2,mm1
paddw mm2,qword ptr [8*ecx+phmapext]
movq mm4,mm2
psraw mm4,16
pxor mm4,mm5
pand mm2,mm4
packuswb mm0,mm2
psrlq mm0,32

movd dword ptr [edi],mm0

add edi,4
add esi,4
dec bp
jnz btloop

emms

ret
bumpytunel endp

m1 dd -1,-1


;;we:
;;eax - 0
;;ecx - licznik
;;ebp - poczatkowy x
;;ebx - nx 16:16 ror
;;edx - ny 16:16 ror
;envylinedraw proc
;movd mm7,dword ptr[fontcol]
;filup:
;push ebx
;push edx
;shr ebx,16
;shr edx,16
;;mov al,bl
;;mov ah,dl
;mov bh,dl
;;movd mm0,dword ptr ds:[4*ebx+phmap]	  ;phongmapa
;movd mm1,dword ptr ds:[4*ebx+tex3]	 ;envmapa
;;paddusb mm0,mm1
;
;;transparentne RULES
;;punpcklbw mm3,dword ptr ds:[edi+4*ebp]
;;punpcklbw mm2,mm1
;;psrlw mm2,8
;;psrlw mm3,8
;;paddw mm2,mm3
;;psrlw mm2,1
;;packuswb mm0,mm2
;;psrlq mm0,32
;
;;inna metoda na oswietlenie [nie bumpowa bo za duzo bialego]
;;punpcklbw mm3,mm0
;;punpcklbw mm2,mm1
;;psrlw mm2,8
;;psrlw mm3,8
;;paddw mm2,mm3
;;psrlw mm2,1
;;packuswb mm0,mm2
;;psrlq mm0,32
;
;paddusb mm1,mm7
;
;movd dword ptr ds:[edi+4*ebp],mm1
;pop edx
;pop ebx
;stalenx: add ebx,12345678h
;staleny: add edx,12345678h
;inc ebp
;dec ecx
;jnz filup
;ret
;envylinedraw endp


;lxorval dd -1,-1

;we:
;eax - 0
;ecx - licznik
;ebp - poczatkowy x
;ebx - nx 16:16 ror
;edx - ny 16:16 ror
;envylinedrawE proc
;filupE:
;push ebx
;push edx
;shr ebx,16
;shr edx,16
;;mov al,bl
;;mov ah,dl
;mov bh,dl
;movd mm0,dword ptr ds:[4*ebx+phmap]	 ;phongmapa
;movd mm1,dword ptr ds:[4*ebx+tex1]
;paddusb mm0,mm1
;punpcklbw mm2,dword ptr ds:[edi+4*ebp]
;psrlw mm2,8
;punpcklbw mm3,mm0
;psrlw mm3,8
;paddw mm0,mm3
;psrlw mm0,1
;packuswb mm4,mm0
;psrlq mm4,32
;movd dword ptr ds:[edi+4*ebp],mm0
;pop edx
;pop ebx
;stalenx2: add ebx,12345678h
;staleny2: add edx,12345678h
;inc ebp
;dec ecx
;jnz filupE
;ret
;envylinedrawE endp



code ends
end