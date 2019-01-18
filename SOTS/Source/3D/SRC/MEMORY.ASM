.386
code32 segment para public use32 'code'
assume cs:code32,ds:code32,es:code32


public memcopy_
public memfill_


;kopiuje pamiec
;we :
;esi - src
;edi - dest
;ecx - ilosc dd
memcopy_ proc
pushad
cld
rep movsd
popad
ret
endp

;wypelnia pamiec danym elementem
;we:
;edi - dest
;eax - wartosc do wpisania
;ecx - ilosc dd
memfill_ proc
pushad
cld
rep stosd
popad
ret
endp





code32 ends
end