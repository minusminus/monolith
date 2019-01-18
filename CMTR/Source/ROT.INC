;obracanie punktow
;macierz obrotu 3x3
rotate proc
;mov esi,verttbl	   ;tablica pktow obiektu
;mov ebx,wsp3d	      ;tablica pktow po obrocie -> wyjsciowa
;mov edi,macierz	 ;macierz obrotu
;mov ecx,vertexcount	 ;licznik

rotlup:
push di
mov bp,3
rotinner:
push bp
call vmulv
add bx,4	       ;nast pozycja nowego wektora
add di,4	       ;nast wektor w macierzy
pop bp
dec bp
jnz rotinner

pop di
add si,4*6     ;oryginalna -> x,y,z,nx,ny,nz
add bx,4*(9-3)	   ;x,y,z,x2d,y2d,nx,ny,nz,persp -> po obrocie
dec cx
jnz rotlup

ret
endp


