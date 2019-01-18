;procedury rysujace fonty

;c1632 db 0

;edi - gdzie
;es:bp - tablica fontow 8x8
;ax - litera, ah=0,al=ascii
writechar16x16 proc
push edi
push bp
;shl ax,3
;add bp,ax
;mov cx,8
;;mov dh,15	  ;kolor
;mov dx,-1
call charchar
lupyf16:
mov bl,8
mov al,es:[bp]
lupxf16:
rcl al,1
jnc emptyput16
;mov ds:[edi],dh
;mov ds:[edi+1],dh
mov ds:[edi],dx
;mov ds:[edi+320],dh
;mov ds:[edi+321],dh
mov ds:[edi+320],dx
emptyput16:
;add edi,2   ;nast w linii
inc edi
inc edi
dec bl
jnz lupxf16
add edi,320*2-8*2	;nast linia fontu w buforze
inc bp
dec cl
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
;shl ax,3
;add bp,ax
;mov cx,8
;;mov dh,15	  ;kolor
;xor edx,edx
;dec edx
call charchar
lupyf32:
mov bl,8
mov al,es:[bp]
lupxf32:
rcl al,1
jnc emptyput32
;mov ds:[edi],dh
;mov ds:[edi+1],dh
;mov ds:[edi+2],dh
;mov ds:[edi+3],dh
mov ds:[edi],edx
;mov ds:[edi+320],dh
;mov ds:[edi+320+1],dh
;mov ds:[edi+320+2],dh
;mov ds:[edi+320+3],dh
mov ds:[edi+320],edx
;mov ds:[edi+2*320],dh
;mov ds:[edi+2*320+1],dh
;mov ds:[edi+2*320+2],dh
;mov ds:[edi+2*320+3],dh
mov ds:[edi+2*320],edx
;mov ds:[edi+3*320],dh
;mov ds:[edi+3*320+1],dh
;mov ds:[edi+3*320+2],dh
;mov ds:[edi+3*320+3],dh
mov ds:[edi+3*320],edx
emptyput32:
add edi,4   ;nast w linii
dec bl
jnz lupxf32
add edi,320*4-8*4	;nast linia fontu w buforze
inc bp
dec cl
jnz lupyf32
pop bp
pop edi
ret
endp

charchar proc
shl ax,3
add bp,ax
mov cl,8
;mov dh,15	 ;kolor
xor edx,edx
dec edx
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
cmp byte ptr [esi],0
je antipor
mov byte ptr [edi],-1
jmp antidnp
antipor:
;mov bl,0
xor bl,bl

mov eax,[esi-1]
or al,al
jz n1
inc bl
n1:
bswap eax
;cmp al,0
or ah,ah
jz n2
inc bl

n2:
mov eax,[esi-1-320]
call techanti

mov eax,[esi+1+318]
call techanti

cmp bl,3
jbe antidnp  ;to nie wstawiaj pktu
mov byte ptr [edi],-1
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

techanti proc
;cmp al,0
or al,al
jz n3
inc bl
n3:
;cmp ah,0
or ah,ah
jz n4
inc bl
n4:
;shr eax,16
bswap eax
;cmp al,0
or ah,ah
jz n5
inc bl
n5:
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
;mov eax,[esi]	      ;\wskazniki sa w tym wypadku odwrotnie
;mov [edi],eax	      ;/
fld dword ptr[esi]
fstp dword ptr[edi]
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
     push bp
     push edi
     mov cx,320*32
     mov ebx,pomtxt
     xor eax,eax
wrcl:
     mov [edi],eax
     mov [ebx],eax
     add edi,4
     add ebx,4
     dec cx
     jnz wrcl
;     mov edi,pomtxt
;     mov cx,320*32
;     xor eax,eax
;wrclpom:
;     mov [edi],eax
;     add edi,4
;     dec cx
;     jnz wrclpom
     pop edi
     push edi
wslup:
     movzx ax,byte ptr [si]
     cmp al,0
     je endstr
     cmp byte ptr [c1632],0
     jne print32
     call writechar16x16     ;postaw znak
     inc si
     add edi,8*2     ;nastepny znak
     jmp wslup
print32:
     call writechar32x32
     inc si
     add edi,8*4
     jmp wslup
endstr:
     pop esi ;od razu zrodlo do antialiasingu
;push esi    ;jeszcze do upgrade'u na 32 bity
      mov edi,pomtxt
;mov edi,320*64
      mov cl,1
      cmp byte ptr [c1632],0
;      jne antial32
;      mov cl,1
;      jmp doanti
      je doanti
antial32:
      mov cl,4
doanti:
      call antirep
;pop edi      ;zdejmij cel 32 bitowy bufor
;mov esi,pomtxt
;xor edx,edx
;xor eax,eax
;dec eax
;upfont:
;cmp byte ptr ds:[edi],0
      pop bp
      ret
endp

;extrn printfonttbl : near
printfonttbl proc
;      push es
      xor ax,ax
;      movq mm1,qword ptr ds:[fontcol] ;kolor fontu juz przerobiony pod mmx'a
      db 3eh,0fh,6fh,0eh
      dw faddr ;0e5h,05h
      mov cx,320*32
pftlup:
      cmp byte ptr [esi],0
      je nextpoint
;;	punpcklbw mm0,dword ptr [edi]
      db 67h,66h,0fh,60h,07h
;;	psrlw mm0,8
      db 0fh,71h,0d0h,08h
;;	paddusw mm0,mm1
      db 0fh,0ddh,0c1h
;;	packuswb mm3,mm0
      db 0fh,67h,0d8h
;;	psrlq mm3,32
      db 0fh,73h,0d3h,20h
;;	movd dword ptr [edi],mm3
      db 67h,66h,0fh,7eh,1fh

nextpoint:
      inc esi
      add edi,4
      dec cx
      jnz pftlup

;      emms
      db 0fh,77h
;      pop es
      ret
endp
