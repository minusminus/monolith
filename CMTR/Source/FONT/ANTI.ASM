;antyaliasing fonta 32x32
;tymczasowo na ekranie
;ds:si - adres fonta
antialias proc
add si,320
mov bp,32-2
antilm:
inc si		;poza pierwszym pktem w linii
mov cx,32-2
antil:
mov bl,0
cmp byte ptr ds:[si-1],0
je n1
inc bl
n1:
cmp byte ptr ds:[si+1],0
je n2
inc bl
n2:
cmp byte ptr ds:[si-1-320],0
je n3
inc bl
n3:
cmp byte ptr ds:[si-1-319],0
je n4
inc bl
n4:
cmp byte ptr ds:[si-1-318],0
je n5
inc bl
n5:
cmp byte ptr ds:[si+1+320],0
je n6
inc bl
n6:
cmp byte ptr ds:[si+1+319],0
je n7
inc bl
n7:
cmp byte ptr ds:[si+1+318],0
je n8
inc bl
n8:
cmp bl,3
jbe dnp  ;to nie wstawiaj pktu
mov byte ptr ds:[si],15
dnp:
inc si
dec cx
jnz antil
inc si		;nast linia
add si,320-32
dec bp
jnz antilm
ret
endp
