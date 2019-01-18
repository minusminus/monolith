bumpytunel:
         mov     edi,screen_buffer
         mov     esi,tablicexy       ;tablica tunelu
         mov     bx,word ptr [counter]
         shr     bx,1
         mov     bh,bl
         add     bl,bl
         mov     dx,bx
         xor     dx,-1
         mov     bp,320*200         ; liczba pktow ekranu
         movq    mm5,qword ptr [m1]
btloop:
         mov     ecx,[esi]           ;adres texturki w tunelu
         mov     eax,ecx
         add     ch,bh
         add     cl,bl
         add     ah,dh
         add     al,dl
         punpcklbw mm2,dword ptr [4*ecx+textunel]
         mov     ecx,[4*ecx+bumpmap]       ;wez przesuniecie z bumpmapy
         add     ch,ah
         add     cl,al
;dodanie koloru [mmx version]
         psrlw   mm2,8
         paddw   mm2,qword ptr [8*ecx+phmapext]
         movq    mm4,mm2
         psraw   mm4,16
         pxor    mm4,mm5
         pand    mm2,mm4
         packuswb mm0,mm2
         psrlq   mm0,32

         movd    dword ptr [edi],mm0

         add     edi,4
         add     esi,4
         dec     bp
         jnz     btloop
         emms
         ret
;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
badd:
         mov     al,cl
         mov     dl,ch
         add     ax,dx
         shr     ecx,16
         mov     dl,cl
         add     ax,dx
         ret

bsub:
         mov     dl,cl
         sub     ax,dx
         mov     dl,ch
         sub     ax,dx
         shr     ecx,16
         mov     dl,cl
         sub     ax,dx
         cwd
         idiv    word ptr [l3]
         add     ax,12800
         ret
