         mov     edi,bumpmap
         mov     esi,textunel
;liczenie X
         mov     bp,256
mxloop:   ;pierwszy pkt (0 z lewej)
         xor     eax,eax
         mov     [edi],eax
         add     edi,4
         add     esi,4
         mov     bl,256-2
xloop:      ;pkty srodkowe
         xor     eax,eax
         xor     dx,dx
         mov     ecx,[esi+8]         ; ds:[x+1]
         call    badd               ;dodaj skladowe
         mov     ecx,[esi]           ; ds:[x-1]
         call    bsub               ;odejmij poprzednika,dziel i normalizuj
         mov     [edi+4],eax           ;wstaw
         add     edi,4
         add     esi,4
         dec     bl
         jnz     xloop
         xor     eax,eax
         mov     [edi+4],eax
         add     esi,4
         add     edi,4
         dec     bp
         jnz     mxloop
;licz Y
         mov     edi,bumpmap
         mov     esi,textunel
         mov     bx,256
myloop:   ;pierwsza linia (0 z gory)
         xor     eax,eax
         mov     [edi+1],al
         add     edi,4
         add     esi,4
         dec     bx
         jnz     myloop
         mov     edi,bumpmap
         mov     esi,textunel
         mov     bp,256-2     ;linie srodkowe
ysloop:
         mov     bl,256-2
yloop:
         xor     eax,eax
         xor     dx,dx
         mov     ecx,[esi+8*256]         ; ds:[y+1]
         call    badd               ;dodaj skladowe
         mov     ecx,[esi]           ; ds:[y-1]
         call    bsub               ;odejmij poprzednika,dziel i normalizuj
         mov     [edi+4*256+1],al           ;wstaw
         add     edi,4
         add     esi,4
         dec     bl
         jnz     yloop
         dec     bp
         jnz     ysloop
         mov     ebx,256             ;ostatnia linia  ds:[0 z dolu]
my2loop:
         xor     eax,eax
         mov     [edi+4*256+1],al
         add     esi,4
         add     edi,4
         dec     bx
         jnz     my2loop

         mov     esi,bumpmap
         mov     ecx,256*256
andloop:
         and     dword ptr [esi],0ffffh
         add     esi,4
         dec     ecx
         jnz     andloop


