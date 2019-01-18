;generator wezlow
;ax - procedura do generacji
generuj:
         mov     esi,wezly
         mov     bp,26
         mov     dword ptr[y],0c2c80000h     ;-100.0
         push    ax
         mov     ax,word ptr [counter]
         xor     dx,dx
         mov     bx,360
         div     bx
         mov     bx,dx
         shl     bx,2
         mov     di,offset sintbl          ;tablica sinusow 360+90 pozycji
         pop     ax

yglup:
         mov     cl,41
         mov     dword ptr[x],0c3200000h      ;-160.0
xglup:

         call    ax
         add     esi,8               ;nast wezel
         fld     dword ptr[x]        ;zwieksz X
         fadd    dword ptr[l8]
         fstp    dword ptr[x]
         dec     cl
         jnz     xglup
         fld     dword ptr[y]        ;zwieksz Y
         fadd    dword ptr[l8]
         fstp    dword ptr[y]
         dec     bp
         jnz     yglup
         ret
