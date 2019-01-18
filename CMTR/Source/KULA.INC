;generator kuli
kula proc
;mov word ptr[fpuout],bx
fild word ptr[fpuout]
fmul dword ptr[pi180]
fsincos
fstp dword ptr offseteluj[4]	;cos
fstp dword ptr offseteluj[0]	;sin
fld dword ptr[x]
fmul st,st
fld dword ptr[y]
fmul st,st
faddp st(1),st
fadd dword ptr[l40000]
fsqrt			;wz=sqrt(40000+x*x+y*y)
fld st
fadd dword ptr[l100]
fld dword ptr[l1000]
fdivrp st(1),st 	;1000/(100+wz)
fxch st(1)
fld st
fld dword ptr[x]
fxch st(1)
fpatan			;atan(x/wz)
fxch st(1)
fld dword ptr[y]
fxch st(1)
fpatan			;atan(y/wz)
fld st(2)
fmulp st(1),st		;atan*1000/(100+wz)
fxch st(1)
fmulp st(2),st
fxch st(1)
fmul dword ptr[l190]	;xt=190*atan*1000/(100+wz)
fxch st(1)
fmul dword ptr[l190]	;yt
fxch st(1)
fld dword ptr[l100]
fld st
;fmul dword ptr[edi+4*ebx]	 ;100*sin(start*pi/180)
fmul dword ptr offseteluj[0]
fxch st(1)
;fmul dword ptr[edi+4*ebx+90*4]  ;100*cos(start*pi/180)
fmul dword ptr offseteluj[4]
fxch st(1)
faddp st(2),st		;xt+100*sin
faddp st(2),st		;yt+100*cos
fmul dword ptr[l256]	;xt*256
fxch st(1)
fmul dword ptr[l256]	;yt*256
fxch st(1)
fistp dword ptr[esi+0]	;X
fistp dword ptr[esi+4]	;Y
ret
endp