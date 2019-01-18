;ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
;³ Z "klockow" tworzymy texturke 00					     ³
;ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ

	mov   edi,temp_seg1
	mov   al,1
	mov   esi, o PlasmaPoint8
	call  MakePlasma

	mov   edi,temp_seg2
	mov   al, 128
	mov   esi, o PlasmaPoint6
;	 call  MakePlasma

	mov   edi,temp_seg3
	mov   al, 128
	mov   esi, o PlasmaPoint1
	call  MakePlasma

	mov   esi,temp_seg1
	mov   ecx,10
;	 call  GfxFX_Blur

	xor   eax,eax
	mov   edi,temp_seg1
	mov   ebx,o pattern2
;	 call  GfxFX_AddPattern

	mov   edi,txt0
	mov   esi,temp_seg1
	mov   edx,000ff03h
;	 mov edx,0
	call  MakeTrueTexture

	xor   eax,eax
	mov   edi,txt0
	mov   ebx,o pattern1
;	 call  GfxFX_AddPattern

	mov   esi,txt0
	mov   ecx,20 ;9
	call  GfxFX_Blur

	mov   esi,txt0
	mov   ebp,5
;	 call  GfxFX_Fuck

