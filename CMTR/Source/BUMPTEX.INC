;bumpuje texture 256x256x32bit
bumptexture proc
mov edi,bumpmap
mov esi,textunel

push edi esi edi edi

;liczenie X
mov bp,256
mxloop:   ;pierwszy pkt (0 z lewej)
xor ax,ax
mov [edi],ax
add edi,4
add esi,4
;mov bx,256-2
mov bl,256-2
;jmp xrrjump
xloop:	    ;pkty srodkowe
xor ax,ax
xor dx,dx
mov ecx, [esi+8]	 ; ds:[x+1]
call badd		;dodaj skladowe
mov ecx, [esi]		 ; ds:[x-1]
call bsub		;odejmij poprzednika,dziel i normalizuj
;lea eax, ds:[eax+ebx-256]
mov  [edi+4],ax 	  ;wstaw
add edi,4
add esi,4
dec bl
jnz xloop
;mov ecx, ds:[esi-4]	     ;ostatni pkt w linii  ds:[0 z prawej]
xrrjump:
xor ax,ax
;xor dx,dx
;call bsub
;mov ax,128
mov  [edi+4],ax
add esi,4
add edi,4
dec bp
jnz mxloop

;licz Y
;mov edi,bumpmap
pop edi
;mov esi,textunel
;mov ebp,200
mov bx,256
myloop:   ;pierwsza linia (0 z gory) i ostatnia linia
xor ax,ax
mov  [edi+1],al
mov [edi+255*256*4+1],al
add edi,4
;add esi,4
dec bx
jnz myloop
;mov edi,bumpmap
;mov esi,textunel
pop edi esi
mov bp,256-2	 ;linie srodkowe
ysloop:
;mov ebx,256
mov bl,256-2
yloop:
xor ax,ax
xor dx,dx
mov ecx, [esi+8*256]	     ; ds:[y+1]
call badd		;dodaj skladowe
mov ecx, [esi]		 ; ds:[y-1]
call bsub		;odejmij poprzednika,dziel i normalizuj
;lea eax, ds:[eax+ebx-256]
mov  [edi+4*256+1],al		;wstaw
add edi,4
add esi,4
dec bl
jnz yloop
dec bp
jnz ysloop
;mov bx,256		;ostatnia linia  ds:[0 z dolu]
;my2loop:
;mov ecx, ds:[esi-4*256]
;xor eax,eax
;xor dx,dx
;call bsub
;mov ax,128
;mov  [edi+4*256+1],al
;add esi,4
;add edi,4
;dec bx
;jnz my2loop

;mov esi,bumpmap
pop esi
;mov ecx,256*256
xor cx,cx
andloop:
;mov eax, ds:[esi]
;and dword ptr ds:[esi],0ffffh
mov word ptr [esi+2],0
;mov  ds:[esi],eax
add esi,4
;dec ecx
inc cx
jnz andloop

ret
bumptexture endp

badd proc
mov al,cl
mov dl,ch
add ax,dx
shr ecx,16
mov dl,cl
add ax,dx
ret
badd endp

bsub proc
mov dl,cl
sub ax,dx
mov dl,ch
sub ax,dx
shr ecx,16
mov dl,cl
sub ax,dx
cwd
idiv word ptr [l3]
add ax,12800
ret
bsub endp
