;procka do tla greetsuf
calcshit proc
fld dword ptr[edi+4*ebx]
fld dword ptr[edi+4*ebx+90*4]
fmul dword ptr[lC]
fxch st(1)
fmul dword ptr[lD]
fxch st(1)			;Dcos(start*pi/180),Csin(start*pi/180)
fild dword ptr[start]
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
fmul dword ptr[lB]	 ;Bcos(...)
fxch st(1)
fsin
fmul dword ptr[lA]	 ;Asin(...)
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
fmul dword ptr[llE]	  ;wz=Esqrt(...)
fadd dword ptr[wz]	;wz+=...
fstp dword ptr[wz]

ret
endp