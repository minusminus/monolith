.586
code segment public use16
assume cs:code,ds:code,es:code


org 100h

start:

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
	movzx	ebp, byte ptr usintbl[ebp]

	add	ebp, ebx
	add	ebp, edx
	and	ebp, 0ffh
	movzx	ebp, byte ptr usintbl[ebp]

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
	movzx	ebp, byte ptr usintbl[ebx]

	mov	bl, cl
	add	bl, cl
	mov	bl, usintbl[ebx]

	add	ebx, ebp
	and	ebx, 0ffh
	mov	bl, usintbl[ebx]

	mov	[edi], bl

	ret
PlasmaPoint2	EndP

PlasmaPoint4	Proc
	xor	ebx, ebx
	mov	bl, dl
	add	bl, al
	movzx	ebp, byte ptr usintbl3[ebx]

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

PlasmaPoint8	Proc
	xor	ebx, ebx
	mov	bl, dl
	add	bl, al
	movzx	ebp, byte ptr usintbl[ebx]


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
	movzx	ebp, byte ptr usintbl2[ebp]

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
	mov	edi, offset _costable
	mov	esi, offset _sintable

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
	mov	esi, offset _sintable
	mov	edi, offset  usintbl
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


	mov	esi, offset _sintable
	mov	edi, offset usintbl2
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

	mov	esi, offset _sintable
	mov	edi, offset usintbl3
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


usintbl db 10 dup (?)
usintbl2 db ?
usintbl3 db ?
_sintable dd ?
_costable dd ?
temp_s dd ?
temp_seg1 dd ?

code ends
end start