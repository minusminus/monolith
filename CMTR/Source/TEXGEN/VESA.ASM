;
;ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
;บฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟบ
;บณ		    vesa library for eos by omen/Dmn			   ณบ
;บภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤูบ
;ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
;
linear_set dd 0
_vesa_bytespp	 dd ?
vesa_screen_size dd ?
vesa_win_size	 dd ?
vesa_bank_inc	 dd ?
_vesa_bpp db 0
_vesa_screen_x dd ?
_vesa_screen_y dd ?
_vesa_screen_addy dd ?
_vesa_screen_bufor dd 0
;-------------- bufor vesy --------------------------
vesa_bufor db 4 dup (?)
win_gran   dw ?
win_size   dw ?
win_seg    dw ?
	   dw 4 dup(?)
vesa_screen_x dw ?
vesa_screen_y dw ?
	   db 3 dup (?)
	   vesa_bypp  db ?
	   db 5 dup (?)
red_size   db ?,?
green_size db ?,?
blue_size  db ?,?
	   db 3 dup (?)
linear_addy dd ?
	   db 212 dup (?)
;อออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออ
;ฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤ vesa_set_mode ฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤ
; info	 : ustawia wybrany tryb vesa i zmienne
; input  : ebx - numer trybu
;	   edx = 0 - bankowanie ekranu
;	       = 1 - linear
; output :  CF = 0 - OK
;	       = 1 - Error
; modified registers : NONE
;ฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤ
vesa_set_mode_ PROC
	pushad
	test [linear_set],-1		      ; czy byl juz ustawiony linear?
	jz nie_zwalniaj
	mov esi,[_vesa_screen_addy]	      ; jak tak to zwolnij jego ...
	mov ah,Free_Physical_Address_Mapping  ; ... mapowanie
	Int_EOS
nie_zwalniaj:
	mov [linear_set],edx
	test edx,edx
	jz no_linear
	or ebx,4000h	   ; jak linear to ustaw bit 14
no_linear:
	mov eax,4f02h	   ; ustaw tryb vesa
	int 10h
	cmp ax,004fh
	je vesa_mode_ok
vesa_error_exit:
	popad
	stc
	retn
vesa_mode_ok:
	mov ecx,ebx
	and ecx,3fffh			; numer trybu
	mov eax,offset vesa_bufor	; adres bufora
	call vesa_mode_info_
	jc vesa_error_exit		; error ( bardzo watpliwe :) ?
	mov al,[red_size]		; potem poustawiaj rozne zmienne
	add al,[green_size]
	add al,[blue_size]
	mov [_vesa_bpp],al		; bity na pixel
	xor eax,eax
	mov ax,[vesa_screen_x]
	mov [_vesa_screen_x],eax	; szer. ekranu
	mov ax,[vesa_screen_y]
	mov [_vesa_screen_y],eax	; wys. ekranu
	movzx ecx,[vesa_bypp]
	add ecx,7
	shr ecx,3
	mov [_vesa_bytespp],ecx 	; bajty na pixel
	mov eax,[_vesa_screen_x]
	mul [_vesa_screen_y]
	mul ecx
	shr eax,2
	mov [vesa_screen_size],eax	; ilosc dwordow na ekranie
	movzx ecx,[win_size]
	shl ecx,8
	mov [vesa_win_size],ecx 	; rozmiar okna w dwordach
	mov ax,[win_size]
	xor dx,dx
	div [win_gran]
	movzx eax,ax
	mov [vesa_bank_inc],eax 	; przyrost gran. na bank
	test [linear_set],-1
	jz no_linear_x
	mov esi,[linear_addy]
	mov ecx,[vesa_screen_size]
	shl ecx,2
	mov ah,Physical_Address_Mapping ; zamapuj lineara
	Int_EOS
	jmp jest_linear
no_linear_x:
	movzx esi,[win_seg]
	shl esi,4
jest_linear:
	sub esi,[code32_addr]
	mov [_vesa_screen_addy],esi	; adres ekranu
	popad
	clc
	ret
vesa_set_mode_ ENDP
;อออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออ
;ฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤ vesa_mode_info ฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤ
; info	 : pobiera informacje o trybie vesa do bufora
; input  : eax - adres 256-bajtowego bufora
;	   ecx = tryb vesa
; output :  CF = 0 - OK
;	       = 1 - Error
; modified registers : NONE
; ! bufor powinien lezec ponizej 1 Mb !
;ฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤ
vesa_mode_info_ PROC near
	pushad
	mov edi,eax
	add eax,[code32_addr]
	and edi,15		      ; edi 4-bitowy offset bufora
	shr eax,4		      ; adres segmentu
	mov [Real_es],eax
	mov eax,4f01h		      ; get mode info
	int 10h
	cmp ax,004fh
	jne vesa_error_exit
	popad
	clc
	retn
vesa_mode_info_ ENDP
;อออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออ
;ฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤ vesa_show_screen ฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤ
; info	 : kopiuje bufor na ekran, czysci bufor
; input  : NONE
; output :  NONE
; modified registers : NONE
;ฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤ
; nie chce mi sie tego komentowac :((
xcv dd ?
vesa_show_screen_ PROC
       pushad
       mov esi,[_vesa_screen_bufor]
       test esi,esi
       jz dont_copy
       test [linear_set],-1
       jz vss_nolinear
       mov ecx,[vesa_screen_size]
       mov edi,[_vesa_screen_addy]
       shr ecx,2
       xor eax,eax
do_loop_1:
       fild qword ptr [esi]
       fild qword ptr [esi+8]
       fxch st(1)
       mov dword ptr [esi],eax
       mov dword ptr [esi+4],eax
       fistp qword ptr [edi]
       mov dword ptr [esi+8],eax
       mov dword ptr [esi+12],eax
       fistp qword ptr [edi+8]
       add esi,16
       add edi,16
       dec ecx
       jnz do_loop_1
       ffree st(0)
dont_copy:
       popad
       retn
vss_nolinear:
       mov eax,4f05h
       xor ebx,ebx
       mov edx,ebx
       int 10h

       mov ebp,[vesa_screen_size]
       cld
loop_copy:
       mov edi,[_vesa_screen_addy]
       mov ecx,[vesa_win_size]
       cmp ecx,ebp
       jbe copy_win
       mov ecx,ebp
copy_win:
       sub ebp,ecx
       shr ecx,2
       xor eax,eax
do_loop_2:
       fild qword ptr [esi]
       fild qword ptr [esi+8]
       fxch st(1)
       mov dword ptr [esi],eax
       mov dword ptr [esi+4],eax
       mov dword ptr [esi+8],eax
       mov dword ptr [esi+12],eax
       fistp qword ptr [edi]
       fistp qword ptr [edi+8]
       add esi,16
       add edi,16
       dec ecx
       jnz do_loop_2
       mov eax,4f05h
       mov ebx,100h
       int 10h
       add edx,[vesa_bank_inc]
       mov eax,4f05h
       xor ebx,ebx
       int 10h
       test ebp,ebp
       jnz loop_copy
       popad
       retn
vesa_show_screen_ ENDP
; ออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออ
