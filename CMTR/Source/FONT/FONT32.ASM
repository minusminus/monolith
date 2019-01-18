;wziecie i obrobka fonta
;cs:si - string
;dl - 16,czy 32
;edi - bufor
;ebx - przesuniecie w buforze
dostring proc
push dx edi
add edi,ebx	;gdzie
call writestr	;wypisz string w buforze
pop edi dx
mov esi,edi	;przygotowanie do antialiasingu
mov edi,pomtxt
cmp dl,32
je anty32
mov cx,4	 ;tyle w foncie 16x16
jmp doanty
anty32:
mov cx,4	;tyle przejsc dla 32x32
doanty:
call anty

ret
endp


;cs:si - string
;edi - start
;dl - 16 lub 32 - fonty 32x32, czy 16x16
writestr proc
mov ebp,fonty
strl:
movzx al,byte ptr cs:[si]
cmp al,0
je endstr
push ebp
;mov ah,0
shl eax,3
add ebp,eax
push edi
push dx
cmp dl,32
jne do16x16
call writechar32
pop dx
pop edi
add edi,32*4
jmp nextfont
do16x16:
call writechar16
pop dx
pop edi
add edi,16*4
nextfont:
pop ebp
inc si
jmp strl
endstr:
ret
endp

writechar32 proc
mov bx,8
;mov ah,15
xor edx,edx
dec edx
lupm:
mov cx,8
mov al,[ebp]
lup:
rcl al,1
jnc noput
mov ds:[edi],edx
mov ds:[edi+1*4],edx
mov ds:[edi+2*4],edx
mov ds:[edi+3*4],edx
mov ds:[edi+320*4],edx
mov ds:[edi+320+1*4],edx
mov ds:[edi+320+2*4],edx
mov ds:[edi+320+3*4],edx
mov ds:[edi+2*320*4],edx
mov ds:[edi+2*320*4+1*4],edx
mov ds:[edi+2*320*4+2*4],edx
mov ds:[edi+2*320*4+3*4],edx
mov ds:[edi+3*320*4],edx
mov ds:[edi+3*320*4+1*4],edx
mov ds:[edi+3*320*4+2*4],edx
mov ds:[edi+3*320*4+3*4],edx
noput:
add edi,4*4
dec cx
jnz lup
add edi,(4*320-8*4)*4
inc ebp
dec bx
jnz lupm
ret
endp

writechar16 proc
mov bx,8
;mov ah,15
xor edx,edx
dec edx
lupm16:
mov cx,8
mov al,[ebp]
lup16:
rcl al,1
jnc noput16
mov ds:[edi],edx
mov ds:[edi+1*4],edx
mov ds:[edi+320*4],edx
mov ds:[edi+320+1*4],edx
noput16:
add edi,2*4
dec cx
jnz lup16
add edi,(2*320-8*2)*4
inc ebp
dec bx
jnz lupm16
ret
endp

;we:
;esi - source	-> tu tez wynik
;edi - dest	-> pomocnicza tablica
;cx - ilosc przejsc procedury
anty proc
aloop:
push cx edi esi
call antialias
pop edi esi cx
dec cx
jnz aloop
ret
endp

;antyaliasing fonta 32x32 powinno dzialac tez dla 16x16 bo sa w takich
;samych tablicach
;esi - adres fonta
;edi - gdzie stawiac
antialias proc
add esi,320*4
add edi,320*4
mov bp,32-2
antilm:
add esi,4	   ;poza pierwszym pktem w linii
add edi,4
mov cx,320-2		;cale linie od razu
antil:
cmp dword ptr ds:[esi],0
je por
mov dword ptr ds:[edi],-1
jmp dnp
por:
mov bl,0
cmp dword ptr ds:[esi-1*4],0
je n1
inc bl
n1:
cmp dword ptr ds:[esi+1*4],0
je n2
inc bl
n2:
cmp dword ptr ds:[esi-1*4-320*4],0
je n3
inc bl
n3:
cmp dword ptr ds:[esi-1*4-319*4],0
je n4
inc bl
n4:
cmp dword ptr ds:[esi-1*4-318*4],0
je n5
inc bl
n5:
cmp dword ptr ds:[esi+1*4+320*4],0
je n6
inc bl
n6:
cmp dword ptr ds:[esi+1*4+319*4],0
je n7
inc bl
n7:
cmp dword ptr ds:[esi+1*4+318*4],0
je n8
inc bl
n8:
cmp bl,3
jbe dnp  ;to nie wstawiaj pktu
mov dword ptr ds:[edi],-1
dnp:
add esi,4
add edi,4
dec cx
jnz antil
add esi,4	   ;nast linia
add edi,4
add esi,(320-32)*4
add edi,(320-32)*4
dec bp
jnz antilm
ret
endp
