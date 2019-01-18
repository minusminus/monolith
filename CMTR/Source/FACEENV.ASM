;screen_buffer dd 0
envy proc
	 pusha
;อออออออออออออออออออออ	  Texturowanko	  อออออออออออออออออออออออออออออออออออ
; z grubsza optymalizowane na _dlugosc_ wiec prosze sie nie nabijac :)
; si - fejs
	 mov	 word ptr [tr_part],1
	 mov	 bx,word ptr [si]
	 mov	 di,word ptr [si+8]
	 mov	 si,word ptr [si+4]
	 mov	 ax,word ptr [bx+16]
	 mov	 bp,word ptr [di+16]
	 mov	 dx,word ptr [si+16]
	 cmp	 ax,bp
	 jl	 dr_xchg01
	 xchg	 ax,bp
	 xchg	 bx,di
dr_xchg01:
	 cmp	 ax,dx
	 jl	 dr_xchg02
	 xchg	 ax,dx
	 xchg	 bx,si
dr_xchg02:
	 cmp	 dx,bp
	 jl	 dr_xchg03
	 xchg	 dx,bp
	 xchg	 si,di
dr_xchg03:
	 cmp	 ax,bp
	 je	 dr_skip
	 sub	 bp,dx
	 sub	 dx,ax
	 mov	 word ptr [dy32],bp
	 mov	 word ptr [dy21],dx
	 jnz	 no_chk_swap
	 mov	 ax,word ptr [si+12]
	 cmp	 ax,word ptr [bx+12]
	 jge	 no_chk_swap_2
	 xchg	 si,bx
no_chk_swap_2:
	 mov	 byte ptr [tr_part+1],1
	 mov	 eax,dword ptr [si+12]
	 shl	 eax,8
	 add	 eax,80h
	 mov	 dword ptr [dr_konx],eax
no_chk_swap:
	 push	 bx
	 push	 si
	 push	 di
	 mov	 di,offset delty21
	 call	 dr_delta
	 pop	 si
	 mov	 di,offset delty31
	 call	 dr_delta
	 pop	 bx
	 mov	 di,offset delty32
	 call	 dr_delta
	 mov	 si,bx
	 pop	 bx
	 ; bx  - pierwszy punkt
	 ; si  - drugi punkt
	 test	 word ptr [dy21],-1
	 jz	 calc_slope_2
	 fild	 dword ptr [delty31]
	 fisub	 dword ptr [delty21]
	 fdivr	 dword ptr [l256]
	 fild	 dword ptr [delty31+4]
	 fisub	 dword ptr [delty21+4]
	 fild	 dword ptr [delty31+8]
	 fisub	 dword ptr [delty21+8]
calc_slope_ret:
	 fxch	 st(2)
	 fmul	 st(2),st(0)
	 fmulp	 st(1),st(0)
	 fistp	 dword ptr [const_u]
	 fistp	 dword ptr [const_v]
; zamiany delt
	 mov	 eax,dword ptr [delty21]
	 mov	 edx,dword ptr [delty31]
	 cmp	 eax,edx
	 jle	 dr_xchg04
	 mov	 dword ptr [delty21],edx
	 mov	 cx,word ptr [delty31+4]
	 mov	 dx,word ptr [delty31+8]
	 mov	 word ptr [delty21+4],cx
	 mov	 word ptr [delty21+8],dx
	 mov	 edx,eax
dr_xchg04:
	 mov	 dword ptr [deltyx],edx
	 mov	 eax,dword ptr [delty31]
	 mov	 edx,dword ptr [delty32]
	 cmp	 eax,edx
	 jge	 dr_xchg05
	 mov	 dword ptr [delty31],edx
	 mov	 dword ptr [delty32],eax
	 mov	 cx,word ptr [delty32+4]
	 mov	 dx,word ptr [delty32+8]
	 mov	 word ptr [delty31+4],cx
	 mov	 word ptr [delty31+8],dx
dr_xchg05:
; policz wartosci poczatkowe
	 mov	 ax,word ptr [bx+16]
	 mov	 dx,320
	 mul	 dx
	 movzx	 edi,ax
	 shl	 edi,2
	 mov	 esi,dword ptr [bx+12]
	 shl	 esi,8
	 add	 esi,60h
	 mov	 eax,dword ptr [bx+20]
	 mov	 edx,dword ptr [bx+24]
	 shl	 eax,8
	 shl	 edx,8
	 mov	 cx,word ptr [dy21]
	 lea	 ebx,[esi+40h]
	 jmp	 outer_start
outer_loop:
;movd mm7,dword ptr[fontcol]
db 66h,0fh,6eh,3eh
dw faddr;52h,14h
	 pushad
	 sar	 esi,8
	 sar	 ebx,8
	 sub	 bx,si
	 jmp	 inner_start
inner_loop:
	 xor	 ecx,ecx
	 mov	 ch,dh
	 mov	 cl,ah

;	  mov	  ebp,dword ptr [4*ecx+tex3]
;	  mov	  dword ptr [4*esi+edi+bufor],ebp
;	  movd mm1,[4*ecx+tex3]
	 db 67h,66h,0fh,6eh,0ch,8dh,00h,12h,92h,00h
;	  paddusb mm1,mm7
	 db 0fh,0dch,0cfh
;	  movd [4*esi+edi+bufor],mm1
	 db 67h,66h,0fh,7eh,8ch,0b7h,00h,12h,0a9h,00h

	 add	 ax,word ptr [const_u]
	 add	 dx,word ptr [const_v]
	 inc	 si
inner_start:
	 dec	 bx
	 jns	 inner_loop
	 popad
	 add	 ax,word ptr [delty21+4]
	 add	 dx,word ptr [delty21+8]
	 add	 edi,320*4
	 add	 esi,dword ptr [delty21]
	 add	 ebx,dword ptr [deltyx]
outer_start:
	 dec	 cx
	 jns	 outer_loop
	 dec	 byte ptr [tr_part]
	 js	 dr_skip
	 mov	 bp,word ptr [delty31+4]
	 mov	 word ptr [delty21+4],bp
	 mov	 bp,word ptr [delty31+8]
	 mov	 word ptr [delty21+8],bp
	 mov	 ebp,dword ptr [delty31]
	 mov	 dword ptr [delty21],ebp
	 mov	 ebp,dword ptr [delty32]
	 mov	 dword ptr [deltyx],ebp
	 mov	 cx,word ptr [dy32]
	 test	 byte ptr [tr_part+1],1
	 jz	 outer_start
	 mov	 ebx,dword ptr [dr_konx]
	 jmp	 outer_start
dr_skip:
;ออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออ
;	  fninit
;emms
db 0fh,77h
	 popa
	 ret


calc_slope_2:
	 fild	 word ptr [si+12]
	 fisub	 word ptr [bx+12]
	 fdivr	 dword ptr [l256]
	 fild	 word ptr [si+20]
	 fisub	 word ptr [bx+20]
	 fild	 word ptr [si+24]
	 fisub	 word ptr [bx+24]
	 jmp	 calc_slope_ret

dr_delta:
	 pusha
	 add	 si,12
	 add	 bx,12
	 mov	 cx,4
dr_delta_loop:
	 mov	 ax,word ptr [si]
	 sub	 ax,word ptr [bx]
	 mov	 word ptr [fpuout],ax
	 fild	 word ptr [fpuout]
	 add	 si,4
	 add	 bx,4
	 loop	 dr_delta_loop
	 fxch	 st(2)
	 fdivr	 dword ptr [l256]
	 fmul	 st(3),st(0)
	 fmul	 st(2),st(0)
	 fmulp	 st(1),st(0)
	 fistp	 dword ptr [di+4]
	 fistp	 dword ptr [di+8]
	 fistp	 dword ptr [di]
	 popa
	 ret

endp