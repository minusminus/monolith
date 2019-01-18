; esi<-- o Flare1pal
;  Temp_seg1 -> nowa paleta
Conv_f	     proc
	     mov     edi,temp_seg1
	     mov     ecx,128
	     xor     ah,ah
convert_flare:
	     mov     al,[esi]
	     shl     al,2
	     mov     [edi],al

	     mov     al,[esi+1]
	     shl     al,2
	     mov     [edi+1],al

	     mov     al,[esi+2]
	     shl     al,2
	     mov     [edi+2],al

	     mov     [edi+3],ah
	     add     edi,4
	     add     esi,3
	     loop    convert_flare
	     ret
endp

;PlasmaPoint1 -okregi (linie)				  +
;PlasmaPoint2 -"motylki"				  +
;PlasmaPoint3 -poziome sinusowe linie (soft_me)
;PlasmaPoint4 -Krata  (soft_me) 			  +
;PlasmaPoint5 -Krata2  (soft_me)			  +
;PlasmaPoint6 -grube okregi (soft_me)			   +
;PlasmaPoint7 -sinusowe pionowe pasy
;PlasmaPoint8 -duze poszarpane kola (trzeba softowac)	   +
;PlasmaPoint9 - plamy  poszarpane (trzeba softowac)	   +
;PlasmaPoint10 - Flames (trzeba softowac)		   +
;PlasmaPoint11 -prawie random  (trzeba softowac)	   +



PlasmaPointW5	 Proc
	xor	ebx, ebx
	mov	bl, dl
	add	bl, al
	movzx	ebp, b usintbl[ebx]	; sintable[(x&255+inc)&255]

	mov	bl, cl
	add	bl, al
	mov	bl, usintbl[ebx]	; sintable[(y&255+inc)&255]

	add	ebx, ebp
	and	ebx, 0ffh
	add	bl, cl
	add	bl, dl
	mov	bl, usintbl[ebx]	; sintable[(bla+bla2+x+y)&255]

	add	ebx, ebp
	and	ebx, 0ffh
	mov	bl, usintbl[ebx]	; sintable[(bla+bla2)&255]

	shr	bl,2
	mov	[edi], bl

	ret
PlasmaPointW5	 EndP


make_sflare   proc
	     pushad
	     mov     ebp,0
next_scircle:
	     mov     ecx,steps
rys_1scircle:
	     fldpi
	     mov     temp,ecx
	     fimul   temp
	     mov     temp,steps/2
	     fidiv   temp
	     fsin
	     mov     temp,ebp ;rozmiar kola
	     fimul   temp
	     fistp   temp
	     add     temp,32 ;128
	     mov     ebx,temp  ;ebx =X
;	      shl     ebx,;2

	     fldpi
	     mov     temp,ecx
	     fimul   temp
	     mov     temp,steps/2
	     fidiv   temp
	     fcos
	     mov     temp,ebp ;rozmiar kola
	     fimul   temp
	     fistp   temp
	     add     temp,32   ;128
	     mov     edx,temp  ;ebx =Y
	     shl     edx,6 ;8 ;10
	     add     ebx,edx
	     mov     al,[esi]
	     mov     [edi+ebx  ],al ;0FFffFFffh ;eax ;

;	      mov     [edi+ebx+1],al ;***** t e s t
;	      mov     [edi+ebx+2],al ;***** t e s t
;	      loop    rys_1scircle
	     dec ecx
	     jnz rys_1scircle
	     inc     ebp
	     add     esi,1
	     cmp     ebp,31 ;127
	     jbe     next_scircle

	mov	 edi,Temp_Seg1
	xor	 eax,eax
	mov	 ecx,64*64/4
	rep	 stosd

	mov	 esi,SFlare
	mov	 edi,Temp_Seg1
	add	 esi,65
	add	 edi,65
	mov	 ebp,0
SFSOFTy:
	mov	 ecx,0
SFSOFTx:
	xor	 ebx,ebx
	xor	 eax,eax
	mov	 bl,[esi   ]
	mov	 al,[esi+1 ]
	add	 ebx,eax
	mov	 al,[esi-1 ]
	add	 ebx,eax
	mov	 al,[esi+64]
	add	 ebx,eax
	mov	 al,[esi-64]
	add	 ebx,eax
	mov	 al,[esi-64+1]
	add	 ebx,eax
	mov	 al,[esi-64-1]
	add	 ebx,eax
	mov	 al,[esi+64+1]
	add	 ebx,eax
	mov	 al,[esi+64-1]
	add	 ebx,eax
	xor	 edx,edx
	mov	 eax,ebx
	mov	 ebx,9
	div	 ebx
	mov	 [edi],al

	add	 edi,1
	add	 esi,1
	inc	 ecx
	cmp	 ecx,62
	jnae	 SFSOFTx
	add	 edi,2
	add	 esi,2
	inc	 ebp
	cmp	 ebp,62
	jnae	 SFSOFTy

	mov	 esi,Temp_Seg1
	mov	 edi,SFlare
	mov	 ecx,64*64/4
	rep	 movsd

	mov	 edi,Temp_Seg1
	xor	 eax,eax
	mov	 ecx,64*64/4
	rep	 stosd

	mov	 esi,SFlare
	mov	 edi,Temp_Seg1
	add	 esi,65
	add	 edi,65
	mov	 ebp,0
SFSOFTy2:
	mov	 ecx,0
SFSOFTx2:
	xor	 ebx,ebx
	xor	 eax,eax
	mov	 bl,[esi   ]
	mov	 al,[esi+1 ]
	add	 ebx,eax
	mov	 al,[esi-1 ]
	add	 ebx,eax
	mov	 al,[esi+64]
	add	 ebx,eax
	mov	 al,[esi-64]
	add	 ebx,eax
	mov	 al,[esi-64+1]
	add	 ebx,eax
	mov	 al,[esi-64-1]
	add	 ebx,eax
	mov	 al,[esi+64+1]
	add	 ebx,eax
	mov	 al,[esi+64-1]
	add	 ebx,eax
	xor	 edx,edx
	mov	 eax,ebx
	mov	 ebx,9
	div	 ebx
	mov	 [edi],al

	add	 edi,1
	add	 esi,1
	inc	 ecx
	cmp	 ecx,62
	jnae	 SFSOFTx2
	add	 edi,2
	add	 esi,2
	inc	 ebp
	cmp	 ebp,62
	jnae	 SFSOFTy2

	mov	 esi,Temp_Seg1
	mov	 edi,SFlare
	mov	 ecx,64*64/4
	rep	 movsd

	     popad
	     ret
make_sflare  endp




;*****************************************************************************
; Tworzy true colorowa texturke z trzech buforow 256*256 ( 1 na skladowa )
; Wejscie:
;  þ EDX - maska dla shr'a (00rrggbb)
;  þ ESI - adres poczatku buforow ( polozonych jeden za drugim: r, g, b )
;  þ EDI - gdzie zapisac utworzona teksture
; Wyjscie:
;  þ brak
;*****************************************************************************
MakeTrueTexture Proc
	pushad

	xor	ecx, ecx
mtt2_pet_y:
	xor	ebp, ebp
mtt2_pet_x:
	mov	ah, [esi]
	test	edx, 0ff0000h
	jz	r_no_shr
	shr	ah, 1
r_no_shr:

	mov	al, [esi + 256*256]
	test	edx, 000ff00h
	jz	g_no_shr
	shr	al, 1
g_no_shr:

	shl	eax, 8

	mov	al, [esi + 256*256*2]
	test	edx, 00000ffh
	jz	b_no_shr
	shr	al, 1
b_no_shr:

	mov	[edi], eax
	inc	esi
	add	edi, 4

	inc	ebp
	cmp	ebp, 256
	jnz	mtt2_pet_x

	inc	ecx
	cmp	ecx, 256
	jnz	mtt2_pet_y
	popad
	ret
MakeTrueTexture EndP



MakeTrueTexture2 Proc
	pushad

	xor	ecx, ecx
mtt2_pet_y2:
	xor	ebp, ebp
mtt2_pet_x2:
	mov	ah, [esi]
;	 cmp	ah,4fh
;	 jb	 r_no_shr2
	xor	ax,bp
r_no_shr2:

	mov	al, [esi + 256*256]
;	 cmp	al,060h
;	 ja	 g_no_shr2
	xor	al,ch
g_no_shr2:

	shl	eax, 8

	mov	al, [esi + 256*256*2]
;	 cmp	 al,7fh
;	 ja	 b_no_shr2
	xor	al,cl
b_no_shr2:

	mov	[edi], eax
	inc	esi
	add	edi, 4

	inc	ebp
	cmp	ebp, 256
	jnz	mtt2_pet_x2

	inc	ecx
	cmp	ecx, 256
	jnz	mtt2_pet_y2
	popad
	ret
MakeTrueTexture2 EndP


;*****************************************************************************
; Generuje plazme ( db 256*256 )
; Wejscie:
;  þ AL  - inkrement
;  þ ESI - adres procki tworzacej punkt
;  þ EDI - gdzie zapisac utworzona plazme
; Wyjscie:
;  þ brak
;*****************************************************************************
MakePlasma	Proc

	xor	ecx, ecx
mp_pet_y:
	xor	edx, edx
mp_pet_x:
	call	esi

	inc	edi

	inc	edx
	cmp	edx, 256
	jnz	mp_pet_x

	inc	ecx
	cmp	ecx, 256
	jnz	mp_pet_y

	ret
MakePlasma	EndP
PlasmaPoint1	Proc
	xor	ebx, ebx
	mov	bl, dl
	add	bl, al
	mov	bl, usintbl[ebx]

	and	eax, 0ffh
	mov	ebp, eax
	add	ebp, ecx
	and	ebp, 0ffh
	movzx	ebp, b usintbl[ebp]

	add	ebp, ebx
	add	ebp, edx
	and	ebp, 0ffh
	movzx	ebp, b usintbl[ebp]

	add	ebx, ebp
	add	ebx, ecx
	and	ebx, 0ffh
	mov	bl, usintbl[ebx]

	add	ebp, ebx
	and	ebp, 0ffh
	mov	bl, usintbl[ebp]

	mov	[edi], bl

	ret
PlasmaPoint1	EndP

PlasmaPoint2	Proc
	xor	ebx, ebx
	mov	bl, dl
	add	bl, al
	mov	bl, usintbl[ebx]

	add	bl, cl
	movzx	ebp, b usintbl[ebx]

	mov	bl, cl
	add	bl, cl
	mov	bl, usintbl[ebx]

	add	ebx, ebp
	and	ebx, 0ffh
	mov	bl, usintbl[ebx]

	mov	[edi], bl

	ret
PlasmaPoint2	EndP

PlasmaPoint3	Proc
	xor	ebx, ebx
	mov	bl, dl
	add	bl, al
	mov	bl, usintbl[ebx]

	add	bl, cl
	movzx	ebp, b usintbl3[ebx]

	mov	bl, cl
	add	bl, al
	mov	bl, usintbl[ebx]

	add	ebp, ebx
	and	ebp, 0ffh
	mov	bl, usintbl[ebp]

	mov	[edi], bl
	ret
PlasmaPoint3	EndP

PlasmaPoint4	Proc
	xor	ebx, ebx
	mov	bl, dl
	add	bl, al
	movzx	ebp, b usintbl3[ebx]

	mov	bl, cl
	add	bl, al
	mov	bl, usintbl3[ebx]

	add	ebx, ebp
	and	ebx, 0ffh
	add	bl, cl
	add	bl, dl

	mov	bl, usintbl[ebx]

	mov	[edi], bl

	ret
PlasmaPoint4	EndP

PlasmaPoint5	Proc
	xor	ebx, ebx
	mov	bl, dl
	add	bl, al
	movzx	ebp, b usintbl3[ebx]

	mov	bl, cl
	add	bl, al
	mov	bl, usintbl3[ebx]

	add	ebx, ebp
	and	ebx, 0ffh
	add	bl, cl
	add	bl, dl
	mov	bl, usintbl[ebx]

	add	ebx, ebp
	and	ebx, 0ffh
	mov	bl, usintbl[ebx]
	mov	[edi], bl

	ret
PlasmaPoint5	EndP

PlasmaPoint6	Proc
	xor	ebx, ebx
	mov	bl, dl
	add	bl, al
	mov	bl, usintbl[ebx]

	and	eax, 0ffh
	mov	ebp, eax
	add	ebp, ecx
	and	ebp, 0ffh
	movzx	ebp, b usintbl[ebp]

	add	ebp, ebx
	add	ebp, edx
	and	ebp, 0ffh
	movzx	ebp, b usintbl2[ebp]

	add	ebx, ebp
	add	ebx, ebp
	add	ebx, ecx
	add	ebx, ecx
	and	ebx, 0ffh
	mov	bl, usintbl3[ebx]

	add	ebp, ebx
	and	ebp, 0ffh
	mov	bl, usintbl[ebp]

	mov	[edi], bl

	ret
PlasmaPoint6	EndP

;PlasmaPoint7	 Proc
;	 xor	 ebx, ebx
;	 mov	 bl,usintbl[eax]
;	 add	 bl, al
;	 mov	 bl, usintbl[ebx]
;
;	 and	 eax, 0ffh
;	 mov	 ebp, eax
;	 add	 ebp, ecx
;	 and	 ebp, 0ffh
;	 movzx	 ebp, b usintbl[ebp]
;
;	 add	 ebp, ebx
;	 add	 ebp, edx
;	 and	 ebp, 0ffh
;	 movzx	 ebp, b usintbl[ebp]
;
;	 add	 ebx, ebp
;	 add	 ebx, ecx
;	 and	 ebx, 0ffh
;	 mov	 bl, usintbl[ebx]
;
;	 add	 ebp, ebx
;	 and	 ebp, 0ffh
;	 mov	 bl, usintbl[ebp]
;
;	 mov	 [edi], bl
;
;	 ret
;PlasmaPoint7	 EndP


PlasmaPoint8	Proc
	xor	ebx, ebx
	mov	bl, dl
	add	bl, al
	movzx	ebp, b usintbl[ebx]


	mov	bl, cl
	add	bl, al
	mov	bl, usintbl[ebx]


	add	ebx, ebp
	and	ebx, 0ffh
	add	bl, cl
	add	bl, dl

	and	eax, 0ffh
	mov	ebp, eax
	add	ebp, ecx
	and	ebp, 0ffh
	movzx	ebp, b usintbl2[ebp]

	add	ebx, ebp
	add	ebx, ecx
	and	ebx, 0ffh
	mov	bl, usintbl2[ebx]

	add	ebp, ebx
	and	ebp, 0ffh
	mov	bl, usintbl2[ebp]
	mov	[edi], bl

	ret
PlasmaPoint8	EndP

PlasmaPoint9	Proc
	xor	ebx, ebx
	mov	bl, dl
	add	bl, al
	mov	bl, usintbl[ebx]

	and	eax, 0ffh
	mov	ebp, eax
	add	ebp, ecx
	and	ebp, 0ffh
	movzx	ebp, b usintbl2[ebp]

	add	ebp, ebx
	add	ebp, edx
	and	ebp, 0ffh
	movzx	ebp, b usintbl2[ebp]

	add	ebx, ebp
	add	ebx, ecx
	and	ebx, 0ffh
	mov	bl, usintbl2[ebx]

	add	ebp, ebx
	and	ebp, 0ffh
	mov	bl, usintbl2[ebp]

	mov	[edi], bl

	ret
PlasmaPoint9	EndP

PlasmaPoint10	 Proc
	xor	ebx, ebx
	mov	bl,usintbl[eax]
	add	bl, al
	mov	bl, usintbl2[ebx]

	and	eax, 0ffh
	mov	ebp, eax
	add	ebp, ecx
	and	ebp, 0ffh
	movzx	ebp, b usintbl[ebp]

	add	ebp, ebx
	add	ebp, edx
	and	ebp, 0ffh
	movzx	ebp, b usintbl3[ebp]

	add	ebx, ebp
	add	ebx, ecx
	and	ebx, 0ffh
	mov	bl, usintbl2[ebx]

	add	ebp, ebx
	and	ebp, 0ffh
	mov	bl, usintbl[ebp]

	mov	[edi], bl

	ret
PlasmaPoint10	EndP

PlasmaPoint11	 Proc
	xor	ebx, ebx
	mov	bl,usintbl3[eax]
	add	bl, al
	mov	bl, usintbl[ebx]

	and	eax, 0ffh
	mov	ebp, eax
	add	ebp, ecx
	and	ebp, 0ffh
	movzx	ebp, b usintbl3[ebp]

	add	ebp, ebx
	add	ebp, edx
	and	ebp, 0ffh
	movzx	ebp, b usintbl3[ebp]

	add	ebx, ebp
	add	ebx, ecx
	and	ebx, 0ffh
	mov	bl, usintbl[ebx]

	add	ebp, ebx
	and	ebp, 0ffh
	mov	bl, usintbl3[ebp]	 ; sintable[(bla+bla2)&255]

	mov	[edi], bl

	ret
PlasmaPoint11	EndP


;*****************************************************************************
; Koloruje texture
; Wejscie:
;  þ ESI - adres textury
;  þ EAX - na jaki kolor kolorowac (0rgb)
;  þ ECX - ile razy kolorowac
;*****************************************************************************
GfxFX_Colorize proc
	       shr   eax,2
	       and   eax,3f3f3f3fh
colorize_agin:
	       push  esi
	       push  ecx
	       mov   ecx,256*256
colriz_Npix:
	       mov   ebx,[esi]
	       shr   ebx,1
	       and   ebx,7f7f7f7fh
	       add   ebx,eax
	       mov   [esi],ebx
	       add   esi,4
	       loop  colriz_Npix
	       pop   ecx
	       pop   esi
	       loop  colorize_agin
	       ret
GfxFX_Colorize endp


;*****************************************************************************
; bluruje texture
; Wejscie:
;  þ ESI - adres textury
;  þ ECX - ile razy zblurowac
;*****************************************************************************
GfxFX_Blur proc
	   mov	 edi,temp_seg1
blur_agin:
	   call  MGfxFX_Blur

	   add	 edi,1
	   add	 esi,1
	   call  MGfxFX_Blur

	   add	 edi,1
	   add	 esi,1
	   call  MGfxFX_Blur
	   sub	 edi,2
	   sub	 esi,2

	   push  esi	     ;
	   push  edi	     ;
	   push  ecx	     ;
	   xchg  edi,esi     ;
	   mov ecx,256*256   ; powraca zblurowana
	   rep	 movsd	     ;
	   pop	 ecx	     ;
	   pop	 edi	     ;
	   pop	 esi	     ;

	   loop  blur_agin

	   ret
GfxFX_Blur endp

;mov   esi,txt1 ;<textura do blura
;mov   edi,temp_seg1

MGfxFX_Blur proc
	   pusha

	   mov	 ecx,256
Mblur_y_l:
	   mov	 ebp,256

Mblur_x_l:

	   mov	 edx,ecx
	   add	 edx,0	   ;y
	   and	 edx,0ffh
	   shl	 edx,8
	   mov	 ebx,ebp
	   add	 ebx,0	   ;x
	   and	 ebx,0ffh
	   add	 edx,ebx
	   shl	 edx,2
	   xor	 ebx,ebx

	   mov	 bl,[esi+edx]
	   shl	 ebx,3 ;2 ;**********
	   mov	 eax,ebx


	   mov	 edx,ecx
	   add	 edx,0	 ;y
	   and	 edx,0ffh
	   shl	 edx,8
	   mov	 ebx,ebp
	   add	 ebx,1	 ;x+1
	   and	 ebx,0ffh
	   add	 edx,ebx
	   shl	 edx,2
	   xor	 ebx,ebx
	   mov	 bl,[esi+edx]
	   add	 eax,ebx

	   mov	 edx,ecx
	   add	 edx,0	 ;y
	   and	 edx,0ffh
	   shl	 edx,8
	   mov	 ebx,ebp
	   sub	 ebx,1	  ;x-1
	   and	 ebx,0ffh
	   add	 edx,ebx
	   shl	 edx,2
	   xor	 ebx,ebx
	   mov	 bl,[esi+edx]
	   add	 eax,ebx


	   mov	 edx,ecx
	   sub	 edx,1	   ;y-1
	   and	 edx,0ffh
	   shl	 edx,8
	   mov	 ebx,ebp
	   sub	 ebx,0	    ;x
	   and	 ebx,0ffh
	   add	 edx,ebx
	   shl	 edx,2
	   xor	 ebx,ebx
	   mov	 bl,[esi+edx]
	   add	 eax,ebx


	   mov	 edx,ecx
	   add	 edx,1	  ;y+1
	   and	 edx,0ffh
	   shl	 edx,8
	   mov	 ebx,ebp
	   add	 ebx,0	  ; x
	   and	 ebx,0ffh
	   add	 edx,ebx
	   shl	 edx,2
	   xor	 ebx,ebx
	   mov	 bl,[esi+edx]
	   add	 eax,ebx


	   mov	 edx,ecx
	   sub	 edx,1	   ;y-1
	   and	 edx,0ffh
	   shl	 edx,8
	   mov	 ebx,ebp
	   sub	 ebx,1	    ;x-1
	   and	 ebx,0ffh
	   add	 edx,ebx
	   shl	 edx,2
	   xor	 ebx,ebx
	   mov	 bl,[esi+edx]
	   add	 eax,ebx

	   mov	 edx,ecx
	   add	 edx,1	   ;y+1
	   and	 edx,0ffh
	   shl	 edx,8
	   mov	 ebx,ebp
	   add	 ebx,1	    ;x+1
	   and	 ebx,0ffh
	   add	 edx,ebx
	   shl	 edx,2
	   xor	 ebx,ebx
	   mov	 bl,[esi+edx]
	   add	 eax,ebx

	   mov	 edx,ecx
	   sub	 edx,1	   ;y-1
	   and	 edx,0ffh
	   shl	 edx,8
	   mov	 ebx,ebp
	   add	 ebx,1	    ;x+1
	   and	 ebx,0ffh
	   add	 edx,ebx
	   shl	 edx,2
	   xor	 ebx,ebx
	   mov	 bl,[esi+edx]
	   add	 eax,ebx


	   mov	 edx,ecx
	   add	 edx,1	   ;y+1
	   and	 edx,0ffh
	   shl	 edx,8
	   mov	 ebx,ebp
	   sub	 ebx,1	    ;x-1
	   and	 ebx,0ffh
	   add	 edx,ebx
	   shl	 edx,2
	   xor	 ebx,ebx
	   mov	 bl,[esi+edx]
	   add	 eax,ebx



;	    xor   edx,edx
;	    mov   ebx,16 ;12 ;5 ;*******
;	    div   ebx

	   shr eax,4

	   mov	 [edi],al

	   add	 edi,4

	   dec	 ebp
	   jnz	 Mblur_x_l

;	    loop  Mblur_y_l
	   dec ecx
	   jnz Mblur_y_l
	   popa
	   ret
MGfxFX_Blur endp

;   mov   edi,txt1
;*****************************************************************************
; Rysuje patern 16x16 na teksturze 256x256
; Wejscie:
;  þ EDI - adres textury
;  þ EAX - kolor patternu
;  þ EBX - adres patternu
;*****************************************************************************
GfxFX_AddPattern proc
		 mov   d es:[kolor_pat],eax
		 mov   ebp,16
pattern_w_y:
		 mov   ecx,16
pattern_w_x:
		 pusha
		 mov   esi,ebx
		 mov   ebp,16
next_line:
		 mov   ecx,2
_2_line:
		 lodsb
		 mov   dl,10000000b
		 mov   dh,8
Kropka:
		 test  al,dl	  ;Jest punkt?
		 jnz	NieKropka
		 mov   d [edi],12345678h
		 kolor_pat=$-4
NieKropka:
		 add   edi,4
		 shr   dl,1
		 dec   dh
		 jnz   Kropka
		 loop  _2_line
		 add   edi,(256-16)*4
		 dec   ebp
		 jnz   next_line
		 popa
		 add   edi,16*4
		 loop  pattern_w_x
		 add   edi,320*12*4
		 dec   ebp
		 jnz   pattern_w_y
		 ret
GfxFX_AddPattern endp



;*****************************************************************************
; Calculate sinus & cosinus for MPD ( uses coprocessor )
; coded by mOtzEl / cRyOGeN^sUSPENd
;
; Ostatnia aktualizacja : 26.07.98
;*****************************************************************************

;*****************************************************************************
; Calculate sinus & cosinus  ( wykorzystuje koprocha !!! )
; Zalozenia :
;  þ zdefiniowane tablice sinus i cosinus ( dw )
;*****************************************************************************
NUMBER	EQU 256 			; ile pozycji w tablicy
MULT	EQU 65536			; mnoznik tablicy sinusa & cosinusa

CalculateSinCos 	Proc
	mov	edi, o _costable
	mov	esi, o _sintable

	mov	ecx, NUMBER		; ile pozycji w tablicy
	finit
pet_sin:
	mov	temp_s, NUMBER
	sub	temp_s, ecx
	fldpi				; zaladuj PI na stos
	fimul	temp_s			; x * PI
	mov	temp_s, NUMBER / 2
	fidiv	temp_s			; ( x * PI ) / (NUMBER / 2)
	fsincos 			; sin( ( x * PI ) / ( NUMBER / 2 ) )
	mov	temp_s, MULT
	fimul	temp_s			; MULT * sin( (x*PI) / (NUMBER / 2))
	frndint 			; zaokraglij do liczby calkowitej
	fistp	temp_s
	mov	eax, temp_s		; zapisz wynik do eax
	mov	[edi], eax
	add	edi, 4			;zapamietaj cosinus w tablicy

	mov	temp_s, MULT
	fimul	temp_s			; MULT * sin( (x*PI) / (NUMBER / 2))
	frndint 			; zaokraglij do liczby calkowitej
	fistp	temp_s
	mov	eax, temp_s		; zapisz wynik do eax
	mov	[esi], eax
	add	esi, 4			;zapamietaj sinus w tablicy

	dec	ecx			; zmniejsz liczbe petli
	jnz	pet_sin

	ret
CalculateSinCos 	EndP

CalculateUSin	Proc
	mov	esi, o _sintable
	mov	edi, o usintbl
	mov	ecx, 256
cus_pet:
	mov	eax, [esi]
	sar	eax, 9
	add	eax, 128
	cmp	eax, 255
	jna	cus_ok
	mov	eax, 255
cus_ok:
	mov	[edi], al

	add	esi, 4
	inc	edi
	dec	ecx
	jnz	cus_pet


	mov	esi, o _sintable
	mov	edi, o usintbl2
	mov	ecx, 256
cus_pet2:
	mov	eax, [esi]
	sar	eax, 9
	add	eax, 128
	cmp	eax, 255
	jna	cus_ok2
	mov	eax, 255
cus_ok2:
	or	al,cl
	mov	[edi], al
	add	esi, 4
	inc	edi
	dec	ecx
	jnz	cus_pet2

	mov	esi, o _sintable
	mov	edi, o usintbl3
	mov	ecx, 256
cus_pet3:
	mov	eax, [esi]
	sar	eax, 9
	add	eax, 128
	cmp	eax, 255
	jna	cus_ok3
	mov	eax, 255
cus_ok3:
	xor	 al,cl
	mov	[edi], al
	add	esi, 4
	inc	edi
	dec	ecx
	jnz	cus_pet3

	ret
CalculateUSin	EndP


;*****************************************************************************
; Zwraca liczbe losowa w bx - made by Mrock/Hellcore
;*****************************************************************************
Random	Proc
	push	eax
	mov	bx, Randmval2
	mov	ax, Randmval
	add	bx, 3132h
	add	ax, 0f1adh
	rol	ax, 2
	mov	Randmval, ax
	ror	bx, 1
	add	bx, ax
	mov	Randmval2, bx
	pop	eax
	ret
Random	EndP

; edi adres textury
; ecx ile razy postawic pixel
; EDX kolor pixela

MakeRndTXT proc

Mrnd_txt1:
	   call  random
	   and	 ebx,0000FFFFh
	   mov	 [edi+ebx*4],EDX
	   loop  Mrnd_txt1
	   ret
MakeRndTXT endp


;mov	 esi,o Flare1pal
;mov	 edi,Flare1 (! to jest offset!)

make_flare   proc
	     pushad
	     mov     ebp,0
next_circle:
	     mov     ecx,steps
rys_1circle:
	     fldpi
	     mov     temp,ecx
	     fimul   temp
	     mov     temp,steps/2
	     fidiv   temp
	     fsin
	     mov     temp,ebp ;rzmiarkola
	     fimul   temp
	     fistp   temp
	     add     temp,128
	     mov     ebx,temp  ;ebx =X
	     shl     ebx,2

	     fldpi
	     mov     temp,ecx
	     fimul   temp
	     mov     temp,steps/2
	     fidiv   temp
	     fcos
	     mov     temp,ebp ;rzmiarkola
	     fimul   temp
	     fistp   temp
	     add     temp,128
	     mov     edx,temp  ;ebx =Y
	     shl     edx,10
	     add     ebx,edx
	     mov     eax,[esi]
	     mov     d [edi+ebx],eax ;0FFffFFffh

;	      loop    rys_1circle
	     dec ecx
	     jnz rys_1circle
	     inc     ebp
	     add     esi,4
	     cmp     ebp,127
	     jbe     next_circle
	     popad
	     ret
make_flare   endp



;ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
;³ pieprzy texture  256x256x32b 					     ³
;³									     ³
;³ Wejscie: ESI adres textury 256*256*4 				     ³
;³	    EBP = 0,1,2 						     ³
;ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
GfxFx_Fuck	proc
		pushad

		mov    ecx,256*256
		xor    ebx,ebx
		xor    eax,eax
Fucktxtup:
		mov    al,[esi]
		mov    bl,[esi+1]
		add    eax,ebx
		mov    bl,[esi+2]
		add    eax,ebx
		mov    ebx,3
		xor    edx,edx
		div    ebx

		mov    [esi+ebp],al
		add    esi,4
		loop   Fucktxtup

		popad
		ret
GfxFx_Fuck	endp






