;rysuje bitmape z wartosci w wezlach
drawbitmap:
         mov     edi,screen_buffer
         mov     esi,wezly
         mov     bp,25
blupy:
         mov     cx,40
blupx:
         call    fill8x8
         add     esi,8   ;nast wezel
         add     edi,8*4   ;nast kwadrat 8x8 na ekranie
         loop    blupx
         add     edi,7*320*4   ;nast czesc
         add     esi,8
         dec     bp
         jnz     blupy
         ret
; ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
; ³          Bitmap interpolation ver. 0.5 by omen/Dmn        ³
; ³             Just a test, almost no optimization           ³
; ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
;bitmap 8x8 filler
;esi - offset w tablicy z wartosciami wezlow
;edi - adres w buforze ekranu
;adres do texturki wpisany przed wywolaniem w odpowiednie miejsce
;dla trybu 320x...x32bpp

fill8x8:
         pushad
         mov     ebx,dword ptr [esi+8]
         sub     ebx,dword ptr [esi]
         mov     ecx,dword ptr [esi+12]
         sub     ecx,dword ptr [esi+4]
         mov     eax,dword ptr [esi+41*8+8]
         sub     eax,dword ptr [esi+41*8]
         mov     edx,dword ptr [esi+41*8+12]
         sub     edx,dword ptr [esi+41*8+4]
         sub     eax,ebx
         sub     edx,ecx
         sar     eax,6
         sar     edx,6
         mov     [deltadx],eax
         mov     [deltady],edx
         sar     ebx,3
         sar     ecx,3
         mov     eax,dword ptr [esi+41*8]
         sub     eax,dword ptr [esi]
         mov     edx,dword ptr [esi+41*8+4]
         sub     edx,dword ptr [esi+4]
         sar     eax,3
         sar     edx,3
         mov     [deltax],eax
         mov     [deltay],edx
         mov     edx,dword ptr [esi+4]
         mov     eax,dword ptr [esi]
         add     edi,4*8
         mov     dword ptr [ll],8
loopy:
         push    edx
         mov     ebp,-8
         push    eax
         movzx   edx,dx
         xchg    dl,ah
loopx:
         mov     esi,dword ptr [4*edx+12345678h] ; uwaga, self-mod
                                                 ; nie przesuwac loopx !
         add     ah,cl
         adc     dh,ch
         add     al,bl
         adc     dl,bh
         mov     dword ptr ds:[edi+4*ebp],esi
         inc     ebp
         jnz     loopx
         pop     eax
         add     edi,320*4
         pop     edx
         add     ebx,[deltadx]
         add     ecx,[deltady]
         add     eax,[deltax]
         add     edx,[deltay]
         dec     dword ptr [ll]
         jnz     loopy
         popad
         ret


;inicjalizuje adres texturki
initbitmap:
         mov     dword ptr loopx[5],eax
         ret





