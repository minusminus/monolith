;sumuje Z face'ow
;we:
;edi - facetbl
;esi - sumaZtbl
;ecx - ilosc widocznych face'ow
sumujz proc

sumloop:
mov bx,[di]
mov bp,[di+4]
mov edx,[di+8]
fld dword ptr ds:[bp+8]
fadd dword ptr ds:[bx+8]
fadd dword ptr ds:[edx+8]
fmul dword ptr[l256]
fistp dword ptr [di+12]
mov [si],edi
add si,4
add di,4*8
dec cx
jnz sumloop


ret
endp