         xor     ebx,ebx
         mov     dx,-128
yphloop:
         mov     bp,-128
xphloop:
         mov     word ptr [fpuout],bp
         fild    word ptr [fpuout]
         fmul    st,st
         mov     word ptr [fpuout],dx
         fild    word ptr [fpuout]
         fmul    st,st
         faddp   st(1),st          ;D^2
         fisubr   word ptr [phrr]
         fst     dword ptr [fpuout]
         test    byte ptr [fpuout+3],80h
         jz      okphdl
         xor     eax,eax
         fstp    st
         jmp     putphcol
okphdl:
         fsqrt                   ;sqrt(r^2-D^2)
         fistp   dword ptr [fpuout]
         mov     al,byte ptr [fpuout]
         shl     al,1
         jnc     okphkk
         mov     al,0ffh
okphkk:
         mov     ah,al
         shl     eax,8
         mov     al,ah
putphcol:
         mov     [4*ebx+phmap],eax
         inc     bx
         inc     bp
         test    bl,bl
         jnz     xphloop
         inc     dx
         test    bh,bh
         jnz     yphloop
