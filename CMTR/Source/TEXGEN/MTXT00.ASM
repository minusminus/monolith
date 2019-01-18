;lepsza do tunelu niz tex.1

	mov   edi,temp_seg1
	mov   al,128
	mov   esi, o PlasmaPoint4
	call  MakePlasma

	mov   edi,temp_seg2
	mov   al, 12
	mov   esi, o PlasmaPoint2
	call  MakePlasma

	mov   edi,txt0
	mov   esi,temp_seg1
	mov   edx,000ff03h
	call  MakeTrueTexture

