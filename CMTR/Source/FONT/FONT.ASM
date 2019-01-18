.486P
code segment use16
assume cs:code,ds:code,es:code,ss:sztos

start:
mov ax,0013h
int 10h

mov dx,0a000h
mov ds,dx
mov es,dx
mov cx,320*200
mov al,0
mov di,0
cld
rep stosb

mov ax,1130h
mov bh,3
int 10h

;push cs
;pop ds

mov byte ptr cs:[c1632],1
mov edi,0
mov si,offset str1
call writestring



wkey:
mov ah,1
int 16h
jz wkey
mov ah,0
int 16h

mov ax,0003h
int 10h
mov ax,4c00h
int 21h






include fonty.inc




str1: db 'COMMUTATOR',0

code ends

sztos segment use16 stack 'stack'
db 256 dup(?)
sztos ends

end start