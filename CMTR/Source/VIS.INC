;----------------------------------------------------------------------
;----------------------------------------------------------------------
;----------------------------------------------------------------------
;wycinanie face'ow odwroconych tylem
;we:
visible proc
;mov esi,facetbl
;mov ecx,facecount
;mov edx,sumaZtbl
;mov ebp,0
xor ebp,ebp

bcloop: 	;petla wycinajaca
mov [edx],esi		;zachowany tu od razu adres
mov eax,[si]	       ;1 wierzcholek
mov di,[si+4]	      ;2
mov bx,[si+8]	      ;3
;mov byte ptr[eax+32],0
;mov byte ptr[di+32],0
;mov byte ptr[bx+32],0

fld dword ptr[eax+0]	;x1
fld dword ptr[eax+4]	;y1
fld dword ptr[bx+0]    ;x3
fld dword ptr[bx+4]    ;y3
fsub dword ptr[di+4]   ;y3-y2
fxch st(1)
fsub dword ptr[di+0]   ;x3-x2
fxch st(2)
fsub dword ptr[di+4]   ;y1-y2
fxch st(3)
fsub dword ptr[di+0]   ;x1-x2
fxch st(3)
fmulp st(2),st		;x32*y12
fmulp st(2),st		;x12*y32
fxch st(1)
fsubrp st(1),st 	;x12*y32-x32*y12
fstp dword ptr[fpuout]
;mov edi,fpuout
;test edi,80000000h
;test dword ptr[fpuout],80000000h
test byte ptr[fpuout+3],80h
;cmp edi,0
jnz notput
;jle notput
add edx,4  ;wstaw face'a adres
mov byte ptr[eax+32],0	 ;\
mov byte ptr[di+32],0	 ; zeruj znacznik perspektywy
mov byte ptr[bx+32],0	 ;/
;inc ebp
inc bp
notput:
add si,4*8	 ;nast. adres
dec cx
jnz bcloop

mov facevis,ebp
ret
endp
