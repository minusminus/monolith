;pierwsza textura (na tunel)

	mov   edi,temp_seg1
	mov   al,1
	mov   esi, o PlasmaPoint1
	call  MakePlasma

	mov   edi,temp_seg2
	mov   al, 128
	mov   esi, o PlasmaPoint2
;	 call  MakePlasma

	mov   edi,temp_seg3
	mov   al, 200
	mov   esi, o PlasmaPoint1
;	 call  MakePlasma

	mov   edi,txt0
	mov   esi,temp_seg1
	mov   edx,000ff03h
	call  MakeTrueTexture
