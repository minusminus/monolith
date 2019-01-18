;mov esi,facetbl
;mov ecx,facecount

normloop:
mov edi,[si]
mov ebp,[si+4]
mov ebx,[si+8]
;tu liczenie normalsow
push si
xor eax,eax
xor edx,edx
mov al,4
mov dl,8
call licznorm
faddp st(1),st
fchs
mov al,0
mov dl,8
call licznorm
fsubp st(1),st
mov al,4
mov dl,0
call licznorm
faddp st(1),st
fchs
pop si
fstp dword ptr[si+24]
fstp dword ptr[si+20]
fstp dword ptr[si+16]

add si,4*8
dec cx
jnz normloop

jmp nonorm

licznorm proc
;push si
mov si,2
oncemore:
fld dword ptr ds:[ebp+eax]
fsub dword ptr[edi+eax]
fld dword ptr[ebx+edx]
fsub dword ptr[edi+edx]
fmulp st(1),st
xchg ax,dx
dec si
jnz oncemore

;pop si
ret
endp


nonorm:
