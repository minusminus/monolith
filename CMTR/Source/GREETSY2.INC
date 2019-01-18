;procka do dla greetsuf
calcshit proc
;fld dword ptr[edi+4*ebx]
;fld dword ptr[edi+4*ebx+90*4]
;mov word ptr[fpuout],bx
fild word ptr[fpuout]
fmul dword ptr[pi180]
fsincos
fmul dword ptr[phrr]
fxch st(1)
fmul dword ptr offseteluj[0]
fxch st(1)			;Dcos(start*pi/180),Csin(start*pi/180)
fild dword ptr[startN]
fld st
faddp st(3),st
fxch st(1)
faddp st(1),st
fxch st(1)		;s+Dc,s+Cs
fmul dword ptr[pi180]
fxch st(1)
fmul dword ptr[pi180]
fxch st(1)
fcos
fmul dword ptr[const_v]       ;Bcos(...)
fxch st(1)
fsin
fmul dword ptr[const_u]       ;Asin(...)
fxch st(1)
fadd dword ptr[y]	;yy
fxch st(1)
fadd dword ptr[x]	;xx
fxch st(1)
fmul st,st
fxch st(1)
fmul st,st
fxch st(1)
faddp st(1),st
fsqrt			;sqrt(xx^2+yy^2)
fmul dword ptr offseteluj[4]	   ;wz=Esqrt(...)
fadd dword ptr[wz]	;wz+=...
fstp dword ptr[wz]

ret
endp