.386
code32 segment use32 public 'code' page
assume cs:code32,ds:code32,es:code32

include scene.inc


public bsort_


align 32
;we:
;esi - tbl1
;edi - tbl2
;ecx - ilosc elementow
;wy:
;posortowane elementy w tbl1
bsort_ proc
pushad
mov tbl1,esi
mov tbl2,edi
mov elnum,ecx

;czyszczenie tablicy offsetow
xor eax,eax
mov ecx,256*4
cld
mov edi,offset offtbl
rep stosd


;liczenie wystapien w kazdej czesci
mov esi,tbl1
mov ecx,elnum
l1:
mov edi,[esi]	;numer [adres face'a]
mov eax,[edi].f_zsum	    ;+ suma zetow
mov ebx,eax
mov edx,eax
mov ebp,eax
and eax,0ffh
and ebx,0ff00h
and edx,0ff0000h
and ebp,0ff000000h
shr ebx,8
shr edx,2*8
shr ebp,3*8	;maski dla poszczegolnych czesci
inc dword ptr offtbl[4*eax+4*0*256]	    ;zwiekszenie poszczegolnych
inc dword ptr offtbl[4*ebx+4*1*256]	    ;licznikow
inc dword ptr offtbl[4*edx+4*2*256]
inc dword ptr offtbl[4*ebp+4*3*256]
add esi,4
dec ecx
jnz l1


;liczenie offsetow w kazdej czesci
mov esi,offset offtbl
mov ebp,2
ll2:
mov ecx,256
xor eax,eax	;jednoczesnie po dwie tablice
xor edx,edx

l2:
mov ebx,[esi]
mov edi,[esi+4*1*256]
mov [esi],eax
mov [esi+4*1*256],edx
lea eax,[eax+4*ebx]
lea edx,[edx+4*edi]
add esi,4
dec ecx
jnz l2

add esi,256*4
dec ebp
jnz ll2


;sortowanie
mov esi,tbl1
mov edi,tbl2
mov ebp,4
mov eax,offset offtbl

ll3:
push ebp
mov ebp,eax	;wstaw adres aktualnej tablicy offsetow
push esi edi
mov ecx,elnum

l3:
mov ebx,[esi]	;adres face'a
mov eax,[ebx].f_zsum ;suma zetow
mov edx,eax
and eax,0ffh
shr edx,8	;\dla nastepnego przejscia
mov [ebx].f_zsum,edx ;/
mov edx,[ebp+4*eax]	;gdzie wstawic
mov [edi+edx],ebx	;wstaw adres
add edx,4
mov [ebp+4*eax],edx	;nowy offset
add esi,4
dec ecx
jnz l3


pop esi edi		;zamiana tablic
lea eax,[ebp+256*4]	;nast. tablica przesuniec
pop ebp
dec ebp
jnz ll3



popad
ret
endp


align 32
offtbl dd 4*256 dup(0)
elnum dd 0
tbl1 dd 0
tbl2 dd 0



code32 ends
end