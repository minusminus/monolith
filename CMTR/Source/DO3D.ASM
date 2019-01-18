render proc



;obrot obiektu i swiatla
mov bx,offset macierz
mov bp,offset alfa	;tablica katow
;call makemat
;====================================
push bx
push bp
;przygotowanie macierzy obrotow
mov si,offset pommat1
call makeidentmatrix
mov si,offset pommat2
push si
call makeidentmatrix
pop di
;mov di,offset pommat2
;obrot Y
fild dword ptr ds:[bp+4]
fmul dword ptr[pi180]
fsincos
fst dword ptr[di]		;cosy
fstp dword ptr[di+32]
fst dword ptr[di+24]		;siny
fchs
fstp dword ptr[di+8]
;obrot X
mov si,offset pommat1
fild dword ptr ds:[bp+0]
fmul dword ptr[pi180]
fsincos
fst dword ptr[si+16]		;cosx
fstp dword ptr[si+32]
fst dword ptr[si+20]		;sinx
fchs
fstp dword ptr[si+28]
mov bx,offset pommat3
call matmul3x3
;obrot Z
mov si,offset pommat2
push si
call makeidentmatrix
pop di
;mov di,offset pommat2
;mov bp,kt
pop bp
fild dword ptr ds:[bp+8]
fmul dword ptr[pi180]
fsincos
fst dword ptr[di+0]		;cosz
fstp dword ptr[di+16]
fst dword ptr[di+4]		;sinz
fchs
fstp dword ptr[di+12]
mov si,offset pommat3
;mov bx,offset pommat1
;mov bx,emat
pop bx
call matmul3x3
;====================================












mov si,offset verttbl		;tablica pktow obiektu [oryginalna]
mov bx,offset wsp3d	   ;tablica pktow po obrocie -> do tych pktow sa adresy
		     ;w face'ach
mov di,offset macierz	      ;macierz obrotu
mov cx,vertexcount     ;licznik
push cx di bx si
call rotate


mov si,offset macierz
;call odwrocmac
;====================================
mov cx,4
lea bx,[si+4*8]
obinner:
mov eax,[si]
xchg eax,dword ptr[bx]
mov [si],eax
add si,4
sub bx,4
dec cx
jnz obinner
;====================================

;mov si,offset verttbl
;mov bx,offset wsp3d
;mov di,offset macierz
;mov cx,vertexcount
pop si bx di cx
;call rotateback
add si,12
add bx,20
call rotate







;dodanie 128 do normalsow
mov si,offset verttbl
mov bx,offset wsp3d
mov di,offset macierz
mov cx,vertexcount
add si,12
add bx,20
naddlop:
fld dword ptr[bx]
fld dword ptr[bx+4]
fld dword ptr[bx+8]
fadd dword ptr[l128]
fistp dword ptr[bx+8]
fadd dword ptr[l128]
fistp dword ptr[bx+4]
fadd dword ptr[l128]
fistp dword ptr[bx]
add bx,4*9
dec cx
jnz naddlop





;sumowanie Z
mov di,offset facetbl
mov si,offset sumaZtbl
mov cx,facecount
;call sumujZ
;====================================
sumloop:
mov bx,[di]
mov bp,[di+4]
mov edx,[di+8]
fld dword ptr ds:[bp+8]
fadd dword ptr ds:[bx+8]
fadd dword ptr ds:[edx+8]
fmul dword ptr[l256]
fistp dword ptr [di+12]
mov [si],edi
add si,4
add di,4*8
dec cx
jnz sumloop
;====================================





;sortowanie sum Z
mov si,offset sumaZtbl
mov cx,facecount
;call bubblesort
;====================================
bos:
mov bp,cx	      ;licznik wewnetrzny

mov di,[si]	      ;\bierzemy 1 element z tablicy
mov eax,[di+12] 	;/i jego wartosc

push si 	       ;dla nastepnej petli

bis:
mov bx,[si]	      ;wez adres akt sprawdzanego elementu
cmp eax,[bx+12] 	;porownaj zapamietana wartosc z nim
jg nochs

;mov [esi],edi		 ;wstaw adres porownujacego elementu [mniejszego]
;mov edi,ebx		 ;wez nowy adres najwiekszego elementu
xchg di,[si]
mov eax,[di+12] 	 ;pobranie nowej wartosci max elementu

nochs:
add si,4	       ;nast element
dec bp
jnz bis

pop si		       ;od razu przesuniety o 1 w dol

;wymiana aktualnie bedacego w rejestrze z pierwszym
xchg di,[si]	;\wstawienie max el na pierwsza pozycje w tablicy
;mov eax,[edi+0]   ;/

add si,4
dec cx
jnz bos

;====================================






;perspektywa dla wierzcholkow
mov di,offset wsp3d
mov cx,vertexcount
;call perspective
;====================================
;====================================
persploop:
;==================================
;perspektywa dla pktu
fld dword ptr[l256]
fld dword ptr[di+8]
fadd dword ptr[distance]	;z+dist
fdivp st(1),st
fld st		      ;skala/(z+dist)
fmul dword ptr[di+0]	;x*skala/(z+dist)
fadd dword ptr[korX]
fistp dword ptr[di+12]	;do x2d
fmul dword ptr[di+4]  ;y*skala/(z+dist)
fadd dword ptr[korY]
frndint
fistp dword ptr[di+16]	;do y2d
;==================================
add di,4*9
dec cx
jnz persploop
;====================================
;====================================






;rysowanie facow
mov di,offset sumaZtbl
mov cx,facecount
drawlup:
mov si,[di]	  ;adres faca
pusha
call envy
popa
add di,4
dec cx
jnz drawlup


nodraw:
ret
endp