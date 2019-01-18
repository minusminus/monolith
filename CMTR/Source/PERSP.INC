;ll256 dd 256.0

;----------------------------------------------------------------------
;----------------------------------------------------------------------
;----------------------------------------------------------------------
;perspektywa dla widocznych trojkatow
;we:
;esi - wsp3d
;cx - vertexcount
;wy:
;policzona perspektywa dla wierzcholkow widocznych trojkatow
perspective proc


persploop:
;mov di,si
;call vertpersp
;==================================
;perspektywa dla pktu
fld dword ptr[l256]
fld dword ptr[di+8]
fadd dword ptr[distance]	;z+dist
fdivp st(1),st
fld st		      ;skala/(z+dist)
fmul dword ptr[di+0]	;x*skala/(z+dist)
fadd dword ptr[korX]
fstp dword ptr[di+12]  ;do x2d
fmul dword ptr[di+4]  ;y*skala/(z+dist)
fadd dword ptr[korY]
frndint
fstp dword ptr[di+16]  ;do y2d
;==================================

add di,4*9
dec cx
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
;vertpersp proc
;fld dword ptr[ll256]
;fld dword ptr[di+8]
;fadd dword ptr[distance]	 ;z+dist
;fdivp st(1),st
;fld st 	       ;skala/(z+dist)
;fmul dword ptr[di+0]	 ;x*skala/(z+dist)
;fadd dword ptr[korX]
;fstp dword ptr[di+12]	;do x2d
;fmul dword ptr[di+4]  ;y*skala/(z+dist)
;fadd dword ptr[korY]
;frndint
;fstp dword ptr[di+16]	;do y2d
;ret
;endp
