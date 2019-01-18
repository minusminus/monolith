; 9   kanalow dostepnych
; 6   pierwszych ( 0 - 5 ) to kanaly melodyczne
; 6-9 perkusja ( bass drum, talerze, tam-tam :)
;
;ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
;ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ
synchr_proc PROC near
       pusha
; ta procka jest wywolywana jak sie cos pojawi na kanale 9 ( liczac od 0 )
     inc byte ptr [border_color]
     mov     dx,3c8h
     mov     al,0
     out     dx,al
     inc     dx
     mov     al,byte ptr [border_color]
     out     dx,al
     out     dx,al
     out     dx,al
       popa
       retn
border_color db 0
synchr_proc ENDP
;ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ

adlib_init:
       pusha
       call adlib_zero
       mov  bx,100h+a_reg_01
       call write_adlib
       mov  bx,0bd00h+a_reg_bd
       call write_adlib
cli
       mov ax,3508h
       int 21h
       mov word ptr ds:[OldVect],bx
       mov word ptr ds:[OldVect+2],es
       mov dx,offset NewInt08
       mov ah,25h
       int 21h
       mov al,36h
       out 43h,al
       mov ax,17039
       out 40h,al
       mov al,ah
       out 40h,al
sti
       popa
       retn

adlib_close:
       pusha
       call adlib_zero
cli
       mov dx,word ptr ds:[OldVect]
       mov ax,word ptr ds:[OldVect+2]
       push ds
       mov ds,ax
       mov ax,2508h
       int 21h
       mov al,36h
       out 40h,al
       mov al,255
       out 40h,al
       out 40h,al
       pop ds
sti
       popa
       retn
;ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
adlib_zero:
       pusha
       mov bx,0f500h
init_loop:
       call write_adlib
       dec bh
       jnz init_loop
       popa
       retn
;ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
write_adlib:
; bh - rejestr, bl - wartosc
         pusha
         mov dx,388h
         mov al,bh
         out dx,al
         call adlib_delay
         inc dx
         mov al,bl
         out dx,al
         call adlib_delay
         popa
         retn
;ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
adlib_delay:
         pusha
         mov cx,40
         mov dx,388h
adlib_delay_loop:
         in al,dx
         loop adlib_delay_loop
         popa
         retn
;ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
NewInt08: sub word ptr cs:[a_counter],100h
          jns no_adlib_int
adlib_int:
          pusha
          mov  ax,cs
          push ds
          push es
          mov  ds,ax
          mov  es,ax
;push es
;mov ax,0b800h
;mov es,ax
;inc byte ptr es:[0]
;pop es
          mov  ax,[a_bpm]
          add  [a_counter],ax
          dec  byte ptr [a_ptrn_row]
          jns  no_new_pattern
          mov  bx,[a_ptrn_played]
          add  bx,2
          cmp  bx,offset a_pattern00
          jne  no_module_restart
          mov  bx,[a_ptrn_restart]
no_module_restart:
          mov  [a_ptrn_played],bx
          mov  di,word ptr [bx]
          mov  bx,di
          mov  al,byte ptr [di]
          mov  [a_ptrn_row],al
          mov cx,10
          xor al,al
          mov di,offset a_channels_cnt
          cld
          rep   stosb
          mov   di,offset a_channels_ptr
          movzx cx,[a_channels]
          lea   si,[bx+1]
          rep   movsw
no_new_pattern:
          movzx  bx,[a_channels]
          dec    bx
          mov    di,bx
          shl    di,1
channels_loop:
          dec    byte ptr [bx+a_channels_cnt]
          jns    no_new_note
          mov    si,word ptr [di+a_channels_ptr]
          mov    al,byte ptr [si]
          mov    ah,al
          test   al,80h
          jnz    pause
          test   al,40h
          jz     load_new_instr
          mov    ah,byte ptr [a_channels_ins+bx]
          jmp    last_instr
load_new_instr:
          mov    ah,byte ptr [si+1]
          inc    word ptr [di+a_channels_ptr]
last_instr:
          mov    byte ptr [a_channels_ins+bx],ah
;          and    al,3fh
;  al - nuta, ah - instrument, bx - kanal
          cmp bx,9
          jne no_synchr_chann
          call synchr_proc
          jmp skip_note
no_synchr_chann:
          pusha
          mov    di,bx
          movzx  bx,byte ptr [di+a_channels_ports] ; bx - offset portu
          movzx  si,ah
          mov    cx,si
          shl    si,3
          add    si,cx
          add    si,cx
          add    si,cx
          add    si,offset a_instr_data   ; si - instrument
          and    ax,3fh
          xor    dx,dx
          mov    bp,12
          div    bp
          add    ax,2         ; ax - oktawa, dx - nuta
          push   si
          mov    si,dx
          shl    si,1
          mov    cx,word ptr [si+a_freq_table]
          pop    si
          cmp    di,6
;          jae    no_key
          or     ch,20h
;no_key:
          shl    ax,8+2
          or     cx,ax                  ; cx - key_on, oktawa, freq.
          mov    bp,bx                  ; bp - offset portu
          shl    bp,8
          mov    bx,di
          shl    bx,8
          add    bh,0b0h
          call   write_adlib
          add    bh,10h
          mov    bl,byte ptr [si+10h]
          call   write_adlib
          mov    bx,bp
          add    bh,20h
          mov    al,4
note_loop:
          mov    bl,byte ptr [si]
          call   write_adlib
          add    bh,3
          mov    bl,byte ptr [si+5]
          call   write_adlib
          inc    si
          add    bh,20h-3
          dec    al
          jnz    note_loop
          add    bh,40h
          mov    bl,byte ptr [si]
          call   write_adlib
          add    bh,3
          call   write_adlib
          mov    bx,di
          shl    bx,8
          add    bh,0a0h
          mov    bl,cl
          call   write_adlib
          add    bh,10h
          mov    bl,ch
          call   write_adlib

          popa
skip_note:
          xor    ax,ax
pause:    and    ah,7fh
          mov    byte ptr [a_channels_cnt+bx],ah
          inc    word ptr [di+a_channels_ptr]
no_new_note:
          sub    di,2
          dec    bx
          jns    channels_loop
          pop  es
          pop  ds
          popa
no_adlib_int:
          inc  word ptr cs:[counter]
;          add dword ptr cs:[startn],4
          dec byte ptr cs:[Count08]
          test byte ptr cs:[Count08],3
          jz OldInt
          push ax
          mov al,20h
          out 20h,al
          pop ax
          iret
OldInt:
          db 0eah
OldVect   dd 0
count08   db 0
a_counter dw 0

;ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
include module.inc
include instr.inc

a_ptrn_played  dw offset a_patterns_table-2
a_channels_ports db 00h,01h,02h,08h,09h,0ah,10h,11h,12h,0ffh
a_freq_table   dw 154h,16bh,181h,198h,1b0h,1cah,1e5h,202h,220h,241h,263h,287h
a_ptrn_row     db 0
a_channels_ptr dw 0,0,0,0,0,0,0,0,0,0
a_channels_ins db 0,0,0,0,0,0,0,0,0,0
a_channels_cnt db 0,0,0,0,0,0,0,0,0,0
