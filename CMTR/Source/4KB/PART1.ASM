         mov     word ptr [counter],0
part1:
         call    bumpytunel
         mov     esi,tytul
         mov     edi,screen_buffer+320*84*4
         mov     cl,0
         mov     ax,word ptr [counter]
         mov     ah,al
         shl     eax,8
         mov     al,ah
         movd    mm0,eax
;         emms
         call    show_text_2
         call    show_screen
         cmp     word ptr [counter],1023
         jl      part1
