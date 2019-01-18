;czesc 3 - greetsy

mov eax,tex2
call initbitmap
mov counter,0
mov fontflash,0

mov esi,gp1

pp3:
push esi
mov ax,offset greetsy
;mov ax,offset kula
call generuj
call drawbitmap

mov bx,10
mov ax,fontflash
;test al,111111b
;jnz nozmiana
;pop esi
;add esi,gp2-gp1
;push esi
;nozmiana:
shr ax,6
cwd
idiv bx
mov bx,dx
mov byte ptr flashcol[bx],0ffh
cmp bx,old
je niezmien
mov old,bx
;mov ax,fontflash
;test ax,111111b
;jnz niezmien
pop esi
add esi,gp2-gp1
push esi
niezmien:
xor bx,bx
call makefontcolor
sub byte ptr flashcol[bx],4

mov edi,bufor+320*4*50
pop esi
push esi
;mov esi,gp1
call printfonttbl
;pop esi


call drop
pop esi

mov ax,counter
cmp ax,4*155
;cmp ax,60
jb pp3