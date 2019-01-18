;generator obiektu
objectgen proc
;generuje punkty [kopiowanie do bufora jako floaty]
mov edi,verttbl
mov esi,offset cubepoints
mov ecx,6*16
xor eax,eax
cploop:
mov al,[esi]
mov word ptr[fpuout],ax
fild word ptr[fpuout]
mov al,[esi+1]
mov word ptr[fpuout],ax
fild word ptr[fpuout]
mov al,[esi+2]
mov word ptr[fpuout],ax
fild word ptr[fpuout]
fstp dword ptr[edi+8]
fstp dword ptr[edi+4]
fstp dword ptr[edi+0]
add esi,3
add edi,4*6
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
add ecx,eax
imul ecx,8*4
add ecx,wsp3d
mov [edi+0],ecx
movzx ecx,byte ptr[esi+1]
add ecx,eax
imul ecx,9*4
add ecx,wsp3d
mov [edi+4],ecx
movzx ecx,byte ptr[esi+2]
add ecx,eax
imul ecx,8*4
add ecx,wsp3d
mov [edi+8],ecx
add esi,3
add edi,8*4
dec edx
jnz expl
ret
endp


