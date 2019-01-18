;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 Show text 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; esi - text
; edi - destination
; cx - 0 - 32x32
;      1 - 16x16
;
show_text:
         movd    mm0,dword ptr [text_color]
show_text_2:
         mov     dx,320*32
         shr     dx,cl
show_text_loop:
         cmp     byte ptr [esi],0
         je      skip_text_pixel
         movd    mm1,dword ptr [edi]
         paddusb mm1,mm0
         movd    dword ptr [edi],mm1
skip_text_pixel:
         inc     esi
         add     edi,4
         dec     dx
         jnz     show_text_loop
         emms
         ret
;컴컴컴컴컴컴컴컴컴컴컴컴컴컴� Write string 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
writestring:
         push    edi
         mov     cx,320*32
         call    memset
         mov     edi,pomtxt
         mov     cx,320*32
         push    edi
         call    memset
         pop     edi
wslup:
         movzx   ax,byte ptr [si]
         cmp     al,0
         je      endstr
         cmp     byte ptr [c1632],0
         jne     print32
         call    writechar16x16     ;postaw znak
         inc     si
         add     edi,8*2     ;nastepny znak
         jmp     wslup
print32:
         call    writechar32x32
         inc     si
         add     edi,8*4
         jmp     wslup
endstr:
         pop     esi ;od razu zrodlo do antialiasingu
         mov     edi,pomtxt
         cmp     byte ptr [c1632],0
         jne     antial32
         mov     cl,2
         jmp     areploop
antial32:
         mov     cl,6
areploop:
         push    esi
         push    edi
         add     esi,320
         add     edi,320
         mov     ax,32-2
antiy:
         mov     dx,320-2
         inc     esi
         inc     edi
antix:
         cmp    byte ptr [esi],0
         je     antipor
         mov    byte ptr ds:[edi],-1
         jmp    antidnp
antipor:
         xor    bl,bl
         cmp    byte ptr ds:[esi-1],0
         je     n1
         inc    bl
n1:
         cmp     byte ptr ds:[esi+1],0
         je      n2
         inc     bl
n2:
         cmp     byte ptr ds:[esi-1-320],0
         je      n3
         inc     bl
n3:
         cmp     byte ptr ds:[esi-1-319],0
         je      n4
         inc     bl
n4:
         cmp     byte ptr ds:[esi-1-318],0
         je      n5
         inc     bl
n5:
         cmp     byte ptr ds:[esi+1+320],0
         je      n6
         inc     bl
n6:
         cmp     byte ptr ds:[esi+1+319],0
         je      n7
         inc     bl
n7:
         cmp     byte ptr ds:[esi+1+318],0
         je      n8
         inc     bl
n8:
         cmp     bl,3
         jbe     antidnp  ;to nie wstawiaj pktu
         mov     byte ptr ds:[edi],-1
antidnp:
         inc     esi
         inc     edi
         dec     dx
         jnz     antix
         inc     esi
         inc     edi
         dec     ax
         jnz     antiy
         pop     esi
         pop     edi
         dec     cl
         jnz     areploop
         ret

;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴� Write char 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
charchar:
         shl     ax,3
         add     bp,ax
         mov     cl,8
         xor     edx,edx
         dec     edx
         ret

;edi - gdzie
;es:bp - tablica fontow 8x8
;ax - litera, ah=0,al=ascii
writechar16x16:
         push    edi
         push    bp
         call    charchar
lupyf16:
         mov     bl,8
         mov     al,es:[bp]
lupxf16:
         rcl     al,1
         jnc     emptyput16
         mov     [edi],dx
         mov     [edi+320],dx
emptyput16:
         inc     edi
         inc     edi
         dec     bl
         jnz     lupxf16
         add     edi,320*2-8*2       ;nast linia fontu w buforze
         inc     bp
         dec     cl
         jnz     lupyf16
         pop     bp
         pop     edi
         ret


;edi - gdzie
;es:bp - tablica fontow 8x8
;ax - litera, ah=0,al=ascii
writechar32x32:
         push    edi
         push    bp
         call    charchar
lupyf32:
         mov     bl,8
         mov     al,es:[bp]
lupxf32:
         rcl     al,1
         jnc     emptyput32
         mov     [edi],edx
         mov     [edi+320],edx
         mov     [edi+2*320],edx
         mov     [edi+3*320],edx
emptyput32:
         add     edi,4   ;nast w linii
         dec     bl
         jnz     lupxf32
         add     edi,320*4-8*4       ;nast linia fontu w buforze
         inc     bp
         dec     cl
         jnz     lupyf32
         pop     bp
         pop     edi
         ret
