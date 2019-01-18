;generator obiektu
objectgen proc
;generuje punkty [kopiowanie do bufora jako floaty]
mov edi,verttbl
mov ebx,wsp3d
mov esi,offset cubepoints
mov ecx,6*16
xor eax,eax
cploop:
movsx eax,byte ptr[esi]
mov dword ptr[fpuout],eax
fild dword ptr[fpuout]
movsx eax,byte ptr[esi+1]
mov dword ptr[fpuout],eax
fild dword ptr[fpuout]
movsx eax,byte ptr[esi+2]
mov dword ptr[fpuout],eax
fild dword ptr[fpuout]
fst dword ptr[edi+8]
fstp dword ptr[ebx+8]
fst dword ptr[edi+4]
fstp dword ptr[ebx+4]
fst dword ptr[edi+0]
fstp dword ptr[ebx+0]
add esi,3
add edi,4*6
add ebx,4*9
dec ecx
jnz cploop

;generuje face'y
mov esi,offset mainface
mov edi,facetbl
mov eax,0
mov edx,20
call expandface 	;facetbl przesuniete odpowiednio w procedurze
mov esi,offset mainface
mov edx,20
add eax,16	;nastepne pkty
call expandface
mov esi,offset mainface
mov edx,20
add eax,16	;nastepne pkty
call expandface
mov esi,offset mainface
mov edx,20
add eax,16	;nastepne pkty
call expandface
mov esi,offset mainface
mov edx,20
add eax,16	;nastepne pkty
call expandface
mov esi,offset mainface
mov edx,20
add eax,16	;nastepne pkty
call expandface
ret
endp



;kopiuje face'y, zamienia numery wierzcholkow na adresy
;esi - tablica oryginalnych numerow
;edi - adres w tablicy face'ow
;eax - wartosc do dodania do numerow wierzcholkow
;edx - ilosc face'ow do przeksztalcenia
expandface proc
expl:
movzx ecx,byte ptr[esi]
dec ecx
add ecx,eax
imul ecx,9*4
add ecx,wsp3d
mov [edi+0],ecx
movzx ecx,byte ptr[esi+1]
dec ecx
add ecx,eax
imul ecx,9*4
add ecx,wsp3d
mov [edi+4],ecx
movzx ecx,byte ptr[esi+2]
dec ecx
add ecx,eax
imul ecx,9*4
add ecx,wsp3d
mov [edi+8],ecx
add esi,3
add edi,8*4
dec edx
jnz expl
ret
endp


