;generator obiektu
objectgen proc
;generuje punkty [kopiowanie do bufora jako floaty]
mov di,offset verttbl
mov si,offset wsp3d
mov bx,offset cubepoints
mov cx,3*16
;xor eax,eax
cploop:
;push bx
mov bp,3
ploopG:
movsx ax,byte ptr[bx]
mov word ptr[fpuout],ax
fild word ptr[fpuout]
inc bx
dec bp
jnz ploopG
;pop bx
;movsx ax,byte ptr[bx+1]
;mov word ptr[fpuout],ax
;fild word ptr[fpuout]
;movsx ax,byte ptr[bx+2]
;mov word ptr[fpuout],ax
;fild word ptr[fpuout]

mov bp,8
ploopC:
fst dword ptr[di+bp]
fst dword ptr[si+bp]
fchs
fst dword ptr[di+bp+4*6*3*16]
fstp dword ptr[si+bp+4*9*3*16]
sub bp,4
jns ploopC


;fst dword ptr[di+4]
;fst dword ptr[bx+4]
;fchs
;fst dword ptr[di+4+4*6*3*16]
;fstp dword ptr[bx+4+4*9*3*16]

;fst dword ptr[di+0]
;fst dword ptr[bx+0]
;fchs
;fst dword ptr[di+0+4*6*3*16]
;fstp dword ptr[bx+0+4*9*3*16]

;add bx,3
add di,4*6
add si,4*9
dec cx
jnz cploop

;generuje face'y
;mov si,offset mainface
mov di,offset facetbl
xor ax,ax
mov bp,6
facegenml:
mov si,offset mainface
mov dx,20
call expandface 	;facetbl przesuniete odpowiednio w procedurze
mov si,offset mainface
mov dx,20
add ax,16      ;nastepne pkty
dec bp
jnz facegenml
ret
;call expandface
;mov si,offset mainface
;mov dx,20
;add eax,16	 ;nastepne pkty
;call expandface
;mov si,offset mainface
;mov dx,20
;add eax,16	 ;nastepne pkty
;call expandface
;mov si,offset mainface
;mov dx,20
;add eax,16	 ;nastepne pkty
;call expandface
;mov si,offset mainface
;mov dx,20
;add eax,16	 ;nastepne pkty
;call expandface
;ret
endp



;kopiuje face'y, zamienia numery wierzcholkow na adresy
;esi - tablica oryginalnych numerow
;edi - adres w tablicy face'ow
;eax - wartosc do dodania do numerow wierzcholkow
;edx - ilosc face'ow do przeksztalcenia
expandface proc
expl:
xor ecx,ecx
movzx cx,byte ptr[si]
dec cx
add cx,ax
imul cx,9*4
add cx,offset wsp3d
mov [di+0],ecx
movzx cx,byte ptr[si+1]
dec cx
add cx,ax
imul cx,9*4
add cx,offset wsp3d
mov [di+4],ecx
movzx cx,byte ptr[si+2]
dec cx
add cx,ax
imul cx,9*4
add cx,offset wsp3d
mov [di+8],ecx
add si,3
add di,8*4
dec dx
jnz expl
ret
endp


