.386
code32 segment public 'code' use32
assume cs:code32,ds:code32,es:code32


public points_


;we:
;esi - face
;edi - bufor
points_ proc near
pushad
mov ebx,[esi]	;p1
mov ebp,[esi+4] ;p2
mov esi,[esi+8] ;p3


fld dword ptr[ebx+4*5]	;z
fistp dword ptr[temp]
cmp dword ptr[temp],0
jle pkt2
fld dword ptr[ebx+4*12]  ;x
fld dword ptr[ebx+4*13]  ;y
fistp dword ptr[temp]
mov eax,temp
fistp dword ptr[temp]
mov edx,temp
cmp eax,0
jle pkt2
cmp eax,200
jge pkt2
cmp edx,0
jle pkt2
cmp edx,320
jge pkt2
mov ebx,320
imul eax,ebx
add eax,edx
mov byte ptr[edi+eax],15


pkt2:
fld dword ptr[ebp+4*5]	;z
fistp dword ptr[temp]
cmp dword ptr[temp],0
jle pkt3
fld dword ptr[ebp+4*12]  ;x
fld dword ptr[ebp+4*13]  ;y
fistp dword ptr[temp]
mov eax,temp
fistp dword ptr[temp]
mov edx,temp
cmp eax,0
jle pkt3
cmp eax,200
jge pkt3
cmp edx,0
jle pkt3
cmp edx,320
jge pkt3
mov ebx,320
imul eax,ebx
add eax,edx
mov byte ptr[edi+eax],15


pkt3:
fld dword ptr[esi+4*5]	;z
fistp dword ptr[temp]
cmp dword ptr[temp],0
jle pkt4
fld dword ptr[esi+4*12]  ;x
fld dword ptr[esi+4*13]  ;y
fistp dword ptr[temp]
mov eax,temp
fistp dword ptr[temp]
mov edx,temp
cmp eax,0
jle pkt4
cmp eax,200
jge pkt4
cmp edx,0
jle pkt4
cmp edx,320
jge pkt4
mov ebx,320
imul eax,ebx
add eax,edx
mov byte ptr[edi+eax],15

pkt4:
popad
ret
endp



temp dd 0


code32 ends

end