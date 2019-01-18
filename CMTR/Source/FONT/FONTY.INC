;procedury rysujace fonty

c1632 db ?

;edi - gdzie
;es:bp - tablica fontow 8x8
;ax - litera, ah=0,al=ascii
writechar16x16 proc
push edi
push bp
shl ax,3
add bp,ax
mov cx,8
mov dh,15	;kolor
lupyf16:
mov bx,8
mov al,es:[bp]
lupxf16:
rcl al,1
jnc emptyput16
mov ds:[edi],dh
mov ds:[edi+1],dh
mov ds:[edi+320],dh
mov ds:[edi+321],dh
emptyput16:
add edi,2   ;nast w linii
dec bx
jnz lupxf16
add edi,320*2-8*2	;nast linia fontu w buforze
inc bp
dec cx
jnz lupyf16
pop bp
pop edi
ret
endp

;edi - gdzie
;es:bp - tablica fontow 8x8
;ax - litera, ah=0,al=ascii
writechar32x32 proc
push edi
push bp
shl ax,3
add bp,ax
mov cx,8
mov dh,15	;kolor
lupyf32:
mov bx,8
mov al,es:[bp]
lupxf32:
rcl al,1
jnc emptyput32
mov ds:[edi],dh
mov ds:[edi+1],dh
mov ds:[edi+2],dh
mov ds:[edi+3],dh
mov ds:[edi+320],dh
mov ds:[edi+320+1],dh
mov ds:[edi+320+2],dh
mov ds:[edi+320+3],dh
mov ds:[edi+2*320],dh
mov ds:[edi+2*320+1],dh
mov ds:[edi+2*320+2],dh
mov ds:[edi+2*320+3],dh
mov ds:[edi+3*320],dh
mov ds:[edi+3*320+1],dh
mov ds:[edi+3*320+2],dh
mov ds:[edi+3*320+3],dh
emptyput32:
add edi,4   ;nast w linii
dec bx
jnz lupxf32
add edi,320*4-8*4	;nast linia fontu w buforze
inc bp
dec cx
jnz lupyf32
pop bp
pop edi
ret
endp


;antyaliasing calego bufora 320x32
;esi - bufor
;edi - wynik
antialias proc
add esi,320
add edi,320
mov bp,32-2
antiy:
mov cx,320-2
inc esi
inc edi
antix:
cmp byte ptr ds:[esi],0
je antipor
mov byte ptr ds:[edi],15
jmp antidnp
antipor:
mov bl,0
cmp byte ptr ds:[esi-1],0
je n1
inc bl
n1:
cmp byte ptr ds:[esi+1],0
je n2
inc bl
n2:
cmp byte ptr ds:[esi-1-320],0
je n3
inc bl
n3:
cmp byte ptr ds:[esi-1-319],0
je n4
inc bl
n4:
cmp byte ptr ds:[esi-1-318],0
je n5
inc bl
n5:
cmp byte ptr ds:[esi+1+320],0
je n6
inc bl
n6:
cmp byte ptr ds:[esi+1+319],0
je n7
inc bl
n7:
cmp byte ptr ds:[esi+1+318],0
je n8
inc bl
n8:
cmp bl,3
jbe antidnp  ;to nie wstawiaj pktu
mov byte ptr ds:[edi],15
antidnp:
inc esi
inc edi
dec cx
jnz antix
inc esi
inc edi
dec bp
jnz antiy
ret
endp

;esi - bufor i wynik
;edi - pomocniczy
;cl - ile razy zrobic antyaliasing fontu
antirep proc
push cx
areploop:
push esi edi cx
call antialias
pop cx esi edi
dec cl
jnz areploop
pop cx
test cl,1
jz nocopy	;jak parzysta liczba to nie kopiuj
mov cx,320*32/4
copyloop:
mov eax,ds:[esi]	;\wskazniki sa w tym wypadku odwrotnie
mov ds:[edi],eax	;/
add esi,4
add edi,4
dec cx
jnz copyloop
nocopy:
ret
endp



;edi - gdzie
;es:bp - fonty
;si - string
;byte ptr cs:[c1632] - 0-16,1-32
writestring proc
push edi
wslup:
movzx ax,byte ptr cs:[si]
cmp al,0
je endstr
cmp byte ptr cs:[c1632],0
jne print32
call writechar16x16	;postaw znak
inc si
add edi,8*2	;nastepny znak
jmp wslup
print32:
call writechar32x32
inc si
add edi,8*4
jmp wslup
endstr:
pop esi ;od razu zrodlo do antialiasingu
mov edi,320*64
cmp byte ptr cs:[c1632],0
jne antial32
mov cl,1
call antirep
ret
antial32:
mov cl,4
call antirep
ret
endp