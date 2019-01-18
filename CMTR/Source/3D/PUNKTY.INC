;testowe rysowanie punktow na ekranie
;esi - adres face'a
punkty proc
mov edi,bufor
mov eax,-1

mov ebp,[esi]
fld dword ptr[ebp+16]
;fmul dword ptr[l3204]
;fadd dword ptr[ebp+12]
fistp dword ptr[fpuout]
mov ebx,fpuout
imul ebx,320
fld dword ptr[ebp+12]
fistp dword ptr[fpuout]
add ebx,fpuout
mov [edi+4*ebx],eax
mov ebp,[esi+4]
fld dword ptr[ebp+16]
;fmul dword ptr[l3204]
;fadd dword ptr[ebp+12]
fistp dword ptr[fpuout]
mov ebx,fpuout
imul ebx,320
fld dword ptr[ebp+12]
fistp dword ptr[fpuout]
add ebx,fpuout
mov [edi+4*ebx],eax
mov ebp,[esi+8]
fld dword ptr[ebp+16]
;fmul dword ptr[l3204]
;fadd dword ptr[ebp+12]
fistp dword ptr[fpuout]
mov ebx,fpuout
imul ebx,320
fld dword ptr[ebp+12]
fistp dword ptr[fpuout]
add ebx,fpuout
mov [edi+4*ebx],eax

ret

;l3204 dd 320.0
endp