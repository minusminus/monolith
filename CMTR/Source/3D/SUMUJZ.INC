;sumuje Z face'ow
;we:
;esi - sumaZtbl
;ecx - ilosc widocznych face'ow
sumujz proc
sumujzloop:
mov edi,[esi]	;wez adres face'a
mov ebp,[edi]	;\
mov edx,[edi+4] ; 3 pkty
mov ebx,[edi+8] ;/
fld dword ptr[ebp+8]
fadd dword ptr[edx+8]
fadd dword ptr[ebx+8]
fistp dword ptr[edi+12]
mov eax,[edi+12]
cmp eax,0
jge dodsuma
inc dword ptr[ujnum]
jmp nextesum
dodsuma:
inc dword ptr[dodnum]
nextesum:
add esi,4
dec ecx
jnz sumujzloop

ret
endp