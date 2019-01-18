;rysuje bitmape z wartosci w wezlach
drawbitmap proc
mov edi,bufor
mov esi,wezly
mov bp,25
blupy:
mov cx,40
blupx:
;push edi esi ecx ebp
call fill8x8
;pop ebp ecx esi edi
add esi,8   ;nast wezel
add edi,8*4   ;nast kwadrat 8x8 na ekranie
dec cx
jnz blupx
add edi,7*320*4   ;nast czesc
add esi,8
dec bp
jnz blupy

ret
endp


; ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
; ³	     Bitmap interpolation ver. 0.5 by omen/Dmn	      ³
; ³		Just a test, almost no optimization	      ³
; ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ

; opt. for PII needed !!!!!!!!!!!!!!!!
;bitmap 8x8 filler
;esi - offset w tablicy z wartosciami wezlow
;edi - adres w buforze ekranu
;adres do texturki wpisany przed wywolaniem w odpwiednie miejsce
;dla trybu 320x...x32bpp

fill8x8 proc near
pushad
   mov ebx,dword ptr [esi+8]
   sub ebx,dword ptr [esi]
   mov ecx,dword ptr [esi+12]
   sub ecx,dword ptr [esi+4]
   mov eax,dword ptr [esi+41*8+8]
   sub eax,dword ptr [esi+41*8]
   mov edx,dword ptr [esi+41*8+12]
   sub edx,dword ptr [esi+41*8+4]
   sub eax,ebx
   sub edx,ecx
   sar eax,6
   sar edx,6
;   mov [deltadx],eax
   mov [x],eax
;   mov [deltady],edx
   mov [y],edx
   sar ebx,3
   sar ecx,3
   mov eax,dword ptr [esi+41*8]
   sub eax,dword ptr [esi]
   mov edx,dword ptr [esi+41*8+4]
   sub edx,dword ptr [esi+4]
   sar eax,3
   sar edx,3
;   mov [deltax],eax
   mov [const_u],eax
;   mov [deltay],edx
   mov [const_v],edx
   mov edx,dword ptr [esi+4]
   mov eax,dword ptr [esi]
   add edi,4*8
;   mov [ll],8
   mov [tr_part],8
loopy:
   push edx
   mov ebp,-8
   push eax
   and edx,65535
   xchg dl,ah
loopx:
   mov esi,dword ptr [4*edx+12345678h]	   ; uwaga, self-mod
					   ; nie przesuwac loopx !
   add ah,cl
   adc dh,ch
   add al,bl
   adc dl,bh
   mov dword ptr ds:[edi+4*ebp],esi
   inc ebp
   jnz loopx
   pop eax
   add edi,320*4
   pop edx
;   add ebx,[deltadx]
   add ebx,[x]
;   add ecx,[deltady]
   add ecx,[y]
;   add eax,[deltax]
   add eax,[const_u]
;   add edx,[deltay]
   add edx,[const_v]
   dec [tr_part]
   jnz loopy
popad
ret
fill8x8 endp


;inicjalizuje adres texturki
initbitmap proc near
   mov dword ptr loopx[5],eax
   ret
initbitmap endp

;align 32
; deltax dd 0
; deltay dd 0
; deltadx dd 0
; deltady dd 0
; ll dd 0




