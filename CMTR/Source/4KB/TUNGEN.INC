        mov     cl,200
        mov     edi,tablicexy
        xor     eax,eax
        fld1
        fild    word ptr [t100]
glupy:
        fild    word ptr [t160]
        mov     dx,320
glupx:
        fld     st(1)
        fmul    st,st
        fld     st(1)
        fmul    st,st
        faddp   st(1),st
        fsqrt
        fidivr  word ptr [radius]
        fistp   word ptr [fpuout]
        fld     st(1)
        fld     st(1)
        fpatan
        fdiv    dword ptr [tpi128]
        fistp   word ptr [fpuout+1]
        mov     ax,word ptr [fpuout]
        mov     dword ptr [edi],eax
        fadd    st,st(2)
        add     edi,4
        dec     dx
        jnz     glupx
        fstp    st
        fadd    st,st(1)
        loop    glupy
        fninit

