.386
code32 segment para public use32 'code'
assume cs:code32,ds:code32,es:code32


public fadein_
public fadeout_
public transput_



;rozjasnia bufor o zadana wartosc
;we:
;esi - bufor
;ebx [bl] - wartosc dodawana
;ecx - dlugosc bufora w dd
fadein_ proc
pushad


fadeinloop:
mov eax,[esi]	;wez element
test eax,0ffffffh
jz skipin

add al,bl
jnc okfi1
mov al,0ffh
okfi1:
add ah,bl
jnc okfi2
mov ah,0ffh
okfi2:
ror eax,16
add al,bl
jnc okfi3
mov al,0ffh
okfi3:
ror eax,16

mov [esi],eax
skipin:
add esi,4
dec ecx
jnz fadeinloop



popad
ret
endp




;zciemnia bufor
;we:
;esi - bufor
;ebx [bl] - wartosc odejmowana
;ecx - dlugosc bufora w dd
fadeout_ proc
pushad


fadeoutloop:
mov eax,[esi]	;wez element
test eax,0ffffffh
jz skipout

sub al,bl
jnc okfo1
mov al,0h
okfo1:
sub ah,bl
jnc okfo2
mov ah,0h
okfo2:
ror eax,16
sub al,bl
jnc okfo3
mov al,0h
okfo3:
ror eax,16

mov [esi],eax
skipout:
add esi,4
dec ecx
jnz fadeoutloop



popad

ret
endp




;dodaje transparentnie do bufora
;we:
;esi - bufor zrodlowy [do dodania]
;edi - bufor docelowy
;ecx - dlugosc w dd
transput_ proc
pushad

transloop:
mov eax,[esi]
mov ebx,[edi]

add al,bl
jnc oktr1
mov al,0ffh
oktr1:
add ah,bh
jnc oktr2
mov ah,0ffh
oktr2:
ror eax,16
ror ebx,16
add al,bl
jnc oktr3
mov al,0ffh
oktr3:
ror eax,16

mov [edi],eax
add edi,4
add esi,4
dec ecx
jnz transloop



popad
ret
endp





code32 ends
end