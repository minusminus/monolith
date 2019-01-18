ll256 dd 256.0

;----------------------------------------------------------------------
;----------------------------------------------------------------------
;----------------------------------------------------------------------
;perspektywa dla widocznych trojkatow
;we:
;
;wy:
;policzona perspektywa dla wierzcholkow widocznych trojkatow
perspective proc
;mov esi,sumaZtbl
;mov ecx,facevis


;debugging
;mov edi,wsp3d
;add edi,(1-1)*4*9
;call vertpersp


persploop:
mov ebp,[esi]

mov edi,[ebp]	;1 wierzcholek
;mov edx,[edi+32]
;test dl,10000000b	 ;czy juz byla liczona perspektywa
;jnz p2
call vertpersp
;or dl,10000000b
;mov [edi+32],edx

p2:
mov edi,[ebp+4] 	;2 wierzcholek
;mov edx,[edi+32]
;test dl,10000000b
;jnz p3
call vertpersp
;or dl,10000000b
;mov [edi+32],edx

p3:
mov edi,[ebp+8] 	;3 wierzcholek
;mov edx,[edi+32]
;test dl,10000000b
;jnz p4
call vertpersp
;or dl,10000000b
;mov [edi+32],edx

p4:
add esi,4
dec ecx
jnz persploop

ret
endp


;----------------------------------------------------------------------
;----------------------------------------------------------------------
;----------------------------------------------------------------------
;perspektywa dla 1 vertexa
;we:
;edi - adres vertexa
;wy:
;policzona perspektywa dla danego vertexa
vertpersp proc
fld dword ptr[ll256]
fld dword ptr[edi+8]
fadd dword ptr[distance]	;z+dist
fdivp st(1),st
fld st		      ;skala/(z+dist)
fmul dword ptr[edi+0]	 ;x*skala/(z+dist)
fadd dword ptr[korX]
fstp dword ptr[edi+12]	;do x2d
fmul dword ptr[edi+4]  ;y*skala/(z+dist)
fadd dword ptr[korY]
frndint
fstp dword ptr[edi+16]	;do y2d
ret
endp
