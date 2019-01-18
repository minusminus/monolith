;generator phongmapy
;edi - bufor
phgen proc
mov edi,phbuf
xor edx,edx
yloop:
xor ebp,ebp
xloop:
mov dword ptr[fpuout],ebp
fild dword ptr[fpuout]
fsub dword ptr[xs]
fmul st,st
mov dword ptr[fpuout],edx
fild dword ptr[fpuout]
fsub dword ptr[ys]
fmul st,st
faddp st(1),st		;D^2
fld dword ptr[rr]	;r^2
fsubrp st(1),st
fst dword ptr[fpuout]
test byte ptr[fpuout+3],80h
jz okdl
xor eax,eax
fstp st
jmp putcol
okdl:
fsqrt			;sqrt(r^2-D^2)
fistp dword ptr[fpuout]
mov al,byte ptr[fpuout]
shl al,1
jnc okkk
mov al,0ffh
;cbw			 ;\wartosc rozszerzona na eax
;cwde			 ;/
okkk:
mov ah,al
shl eax,8
mov al,ah
putcol:
mov [edi],eax

add edi,4
inc ebp
cmp ebp,256
jl xloop
inc edx
cmp edx,256
jl yloop

ret
endp