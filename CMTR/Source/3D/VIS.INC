;----------------------------------------------------------------------
;----------------------------------------------------------------------
;----------------------------------------------------------------------
;wycinanie face'ow odwroconych tylem
;we:
visible proc
;mov esi,facetbl
;mov ecx,facecount
;mov edi,sumaZtbl
mov ebp,0

bcloop: 	;petla wycinajaca
mov [edi],esi		;zachowany tu od razu adres
mov eax,[esi]		;1 wierzcholek
mov edx,[esi+4] 	;2
mov ebx,[esi+8] 	;3

fld dword ptr[eax+0]	;x1
fld dword ptr[eax+4]	;y1
fld dword ptr[ebx+0]	;x3
fld dword ptr[ebx+4]	;y3
fsub dword ptr[edx+4]	;y3-y2
fxch st(1)
fsub dword ptr[edx+0]	;x3-x2
fxch st(2)
fsub dword ptr[edx+4]	;y1-y2
fxch st(3)
fsub dword ptr[edx+0]	;x1-x2
fxch st(3)
fmulp st(2),st		;x32*y12
fmulp st(2),st		;x12*y32
fxch st(1)
fsubrp st(1),st 	;x12*y32-x32*y12
fstp dword ptr[fpuout]
mov edx,fpuout
test edx,80000000h
;cmp edx,0
jnz notput
;jle notput
add edi,4  ;wstaw face'a adres
inc ebp
notput:
add esi,4*8	  ;nast. adres
dec ecx
jnz bcloop

mov facevis,ebp
ret
endp
