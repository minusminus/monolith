;tlo pod greetsy
greetsy proc
mov dword ptr[wz],0
;mov dword ptr[lA],043200000h	 ;160.0
;mov dword ptr[lB],042c80000h	 ;100.0
;mov dword ptr[lC],0c1100000h	 ;-20.0
;mov dword ptr[lD],041200000h	 ;10.0
;mov dword ptr[llE],041200000h	 ;10.0
mov dword ptr[const_u],043200000h    ;160.0
mov dword ptr[const_v],042c80000h    ;100.0
mov dword ptr[phrr],0c1100000h	  ;-20.0
mov dword ptr offseteluj[0],041200000h	  ;10.0
mov dword ptr offseteluj[4],041200000h	 ;10.0
call calcshit
;mov dword ptr[lA],0c3200000h	 ;-160.0
;mov dword ptr[lB],0c2c80000h	 ;-100.0
;mov dword ptr[lC],042700000h	 ;60.0
;mov dword ptr[lD],0c2200000h	 ;-40.0
;mov dword ptr[llE],041200000h	 ;10.0
mov dword ptr[const_u],0c3200000h    ;-160.0
mov dword ptr[const_V],0c2c80000h    ;-100.0
mov dword ptr[phrr],042700000h	  ;60.0
mov dword ptr offseteluj[0],0c2200000h	  ;-40.0
mov dword ptr offseteluj[4],041200000h	 ;10.0
call calcshit


;koncowka
fld dword ptr[wz]
fmul dword ptr[l1_8]
fld st
fadd dword ptr[x]
fxch st(1)
fadd dword ptr[y]
fxch st(1)
fmul dword ptr[l256]
fxch st(1)
fmul dword ptr[l256]
fxch st(1)
fistp dword ptr[esi+0]
fistp dword ptr[esi+4]
ret
endp