;generator szachownicy
szachownica:
         mov     bl,32/4
outlup:
         mov     cx,32*8
inlup:
         mov     bh,32
ininlup:
         mov     [edi],eax
         add     edi,4
         dec     bh
         jnz     ininlup
         xchg    edx,eax
         loop    inlup
;         dec     cx
;         jnz     inlup
         xchg    eax,edx
         dec     bl
         jnz     outlup
         ret

;mov edx,eax
;sar edx,31
;xor eax,edx
;add eax,edx

;*****************************************************************************
; Tworzy true colorowa texturke z trzech buforow 256*256 ( 1 na skladowa )
; Wejscie:
;  þ EDX - maska dla shr'a (00rrggbb)
;  þ ESI - adres poczatku buforow ( polozonych jeden za drugim: r, g, b )
;  þ EDI - gdzie zapisac utworzona teksture
; Wyjscie:
;  þ brak
;*****************************************************************************
MakeTrueTexture:
;         pushad
         xor     cx, cx
mtt2_pet_y:
         xor     bx, bx
mtt2_pet_x:
         mov     ah, [esi]
         test    dl,4
         jz      r_no_shr
         shr     ah, 1
r_no_shr:
         mov     al, [esi + 256*256]
         test    dl,2
         jz      g_no_shr
         shr     al, 1
g_no_shr:
         shl     eax, 8
         mov     al, [esi + 256*256*2]
         test    dl,1
         jz      b_no_shr
         shr     al, 1
b_no_shr:
         mov     [edi], eax
         inc     esi
         add     edi, 4
         inc     bx
         cmp     bh,1
         jnz     mtt2_pet_x
         inc     cx
         cmp     ch,1
         jnz     mtt2_pet_y
;         popad
         ret

;*****************************************************************************
; Generuje plazme ( db 256*256 )
; Wejscie:
;  þ AL  - inkrement
;  þ SI - adres procki tworzacej punkt
;  þ EDI - gdzie zapisac utworzona plazme
; Wyjscie:
;  þ brak
;*****************************************************************************
MakePlasma:
         xor     cx, cx
mp_pet_y:
         xor     dx, dx
mp_pet_x:
         call    si
         inc     edi
         inc     dl
         jnz     mp_pet_x
         inc     cl
         jnz     mp_pet_y
         ret

PlasmaPoint1:
         push    si
         mov     si,0ffh
         xor     bx,bx
         mov     bl, dl
         add     bl, al
         mov     bl, usintbl[bx]

         and     ax, si
         mov     bp, ax
         add     bp, cx
         and     bp, si
         movzx   bp, byte ptr usintbl[bp]

         add     bp, bx
         add     bp, dx
         and     bp, si
         movzx   bp, byte ptr usintbl[bp]

         add     bx, bp
         add     bx, cx
         and     bx, si
         mov     bl, usintbl[bx]

         add     bp, bx
         and     bp, si
         mov     bl, usintbl[bp]

         mov     [edi], bl
         pop     si
         ret

PlasmaPoint2:
         xor     bx, bx
         mov     bl, dl
         add     bl, al
         mov     bl, usintbl[bx]

         add     bl, cl
         movzx   bp, byte ptr usintbl[bx]

         mov     bl, cl
         add     bl, cl
         mov     bl, usintbl[bx]

         add     bx, bp
         and     bx, 0ffh
         mov     bl, usintbl[bx]

         mov     [edi], bl
         ret

PlasmaPoint4:
         xor     bx, bx
         mov     bl, dl
         add     bl, al
         movzx   bp, byte ptr usintbl3[bx]

         mov     bl, cl
         add     bl, al
         mov     bl, usintbl3[bx]

         add     bx, bp
         and     bx, 0ffh
         add     bl, cl
         add     bl, dl

         mov     bl, usintbl[bx]
         mov     [edi], bl
         ret

;*****************************************************************************
; Calculate sinus & cosinus  ( wykorzystuje koprocha !!! )
; Zalozenia :
;  þ zdefiniowane tablice sinus i cosinus ( dw )
;*****************************************************************************
CalculateSinCos:
         mov     di, offset _costable
         mov     si, offset _sintable
         mov     ecx,256             ; ile pozycji w tablicy
pet_sin:
         mov     dword ptr [fpuout],256
         sub     [fpuout], ecx
         fldpi                           ; zaladuj PI na stos
         fimul   dword ptr [fpuout]                  ; x * PI
         mov     dword ptr [fpuout],128
         fidiv   dword ptr [fpuout]                  ; ( x * PI ) / (NUMBER / 2)
         fsincos                         ; sin( ( x * PI ) / ( NUMBER / 2 ) )
         fimul   dword ptr [MULT]                  ; MULT * sin( (x*PI) / (NUMBER / 2))
;         frndint                         ; zaokraglij do liczby calkowitej
         fistp dword ptr[di]
         add     di, 4                  ;zapamietaj cosinus w tablicy
         fimul   dword ptr [MULT]                  ; MULT * sin( (x*PI) / (NUMBER / 2))
;         frndint                         ; zaokraglij do liczby calkowitej
         fistp dword ptr[si]
         add     si, 4                  ;zapamietaj sinus w tablicy
         loop    pet_sin
         ret

CalculateUSin:
         mov     si, offset _sintable
         mov     di, offset usintbl
         mov     cx,256
         push    si
cus_pet:
         call    processSin
         call    endSIN
         jnz     cus_pet
         pop     si

         push    si
         mov     di, offset usintbl2
         mov     ch,1
cus_pet2:
         call    processSIN
         or      al,cl
         call    endSIN
         jnz     cus_pet2
         pop     si
         mov     di,offset usintbl3
         mov     ch,1
cus_pet3:
         call    processSIN
         xor     al,cl
         call    endSIN
         jnz     cus_pet3
         ret

processSIN:
         mov     eax, [si]
         sar     eax, 9
         add     ax, 128
         cmp     ax, 255
         jna     cus_ok
         mov     al, 255
cus_ok:
         ret

endSIN:
        mov     [di], al
        add     si, 4
        inc     di
        dec     cx
        ret
