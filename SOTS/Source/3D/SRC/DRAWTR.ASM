;TRIANGLE ENGINE v2.0
.586
code32 segment use32 para public 'code'
assume cs:code32,ds:code32,es:code32


;plik opisu struktur
include scene.inc


;upublicznienie zmiennych
public w1
public w2
public w3
public y1
public y2
public y3
public z1
public z2
public z3
public dx12
public dx23
public dx13
public y12
public y23
public y13
public dz12
public dz23
public dz13
public dzstale
public dstale
public flags
public licznik
public tr
public fdt
public dir
public l64k
public l64k_256


;upublicznienie procedur
public drawtr_
public inittreng_
public inittrrender_



;zewnetrzne procedury na trojkaty
include trext.inc



;inicjalizacja tiangle engine'u
;we:
;esi - fastdivtbl
inittreng_ proc
pushad
mov fdt,esi

include inittr.inc	 ;inicjalizacja adresow procedur na trojkaty

popad
ret
endp








;inicjalizacja dla danego renderingu
;we:
;esi - zbufor
;edi - bufor
;edx - szerokosc bufora w pikselach
inittrrender_ proc
pushad

mov zbufor,esi
mov bufor,edi
mov scrx,edx
shl edx,2      ;dlugosc linii w bajtach

xor ecx,ecx
initloop:
cmp dword ptr trproc[4*ecx],0
je nextloop
mov eax,dword ptr trinitproc[4*ecx]
call eax		  ;inicjalizuj procedure jesli jest taka
			  ;wszystkie inicjalizery tak samo prametry
			  ;przyjmuja
nextloop:
inc ecx
cmp ecx,256
jb initloop


popad
ret
endp












;glowna procedura rysowania trojkatow
;we:
;esi - adres face'a
drawtr_ proc
pushad

;sortowanie wierzcholkow po Y
mov tr,esi
mov ebp,[esi].f_v3
mov edi,[esi].f_v2
mov esi,[esi].f_v1
fld dword ptr[ebp].v_y2d
fistp dword ptr[temp]
mov eax,temp
fld dword ptr[edi].v_y2d
fistp dword ptr[temp]
mov ebx,temp
fld dword ptr[esi].v_y2d
fistp dword ptr[temp]
mov edx,temp

cmp edx,ebx
jle noch1
xchg edx,ebx
xchg edi,esi
noch1:
cmp edx,eax
jle noch2
xchg eax,edx
xchg esi,ebp
noch2:
cmp ebx,eax
jle noch3
xchg ebx,eax
xchg edi,ebp
noch3:
mov w1,esi
mov w2,edi
mov w3,ebp
mov y1,edx
mov y2,ebx
mov y3,eax


;roznice Y [liczniki dla czesci i offsety do fdt]
fld dword ptr[ebp].v_y2d	;y3
fld dword ptr[edi].v_y2d	;y2
fld dword ptr[esi].v_y2d	;y1
fld st(2)
fld st(2)
fld st(2)		;y1 y2 y3 y1 y2 y3
fsubp st(5),st
fxch st(2)
fsubp st(3),st
fxch st(1)
fsubp st(1),st
fxch st(1)		;y12 y23 y13
fistp dword ptr[y12]
fistp dword ptr[y23]
fistp dword ptr[y13]
mov ebx,y12
mov ecx,y23
mov edx,y13


;ustawienie flag widocznosci
cmp ebx,0
jng nvis12
mov eax,80000000h	;widac czesc 1-2
jmp vis12
nvis12:
xor eax,eax		;nie widac czesci 1-2
vis12:
cmp ecx,0
jng nvis23
or eax,40000000h	;widac czesc 2-3
nvis23:
mov flags,eax
;ustawienie licznika
push edx
xor edx,edx
rcl eax,1
jnc np1
inc edx 	;jak widac ta czesc to zwieksz licznik
np1:
rcl eax,1
jnc np2
inc edx
np2:
mov licznik,edx
pop edx
cmp dword ptr[licznik],0
je koniectr		 ;od razu mozna skonczyc rysowanie


;delty X
mov eax,fdt	;adres do fastdivtbl

fld dword ptr[edi].v_x2d
fld dword ptr[ebp].v_x2d
fld st				;x3 x3 x2
fsub st,st(2)
fxch st(1)
fsub dword ptr[esi].v_x2d
fxch st(2)
fsub dword ptr[esi].v_x2d
fxch st(1)			;x32 x21 x31
fmul dword ptr[eax+4*ecx]
fxch st(2)
fmul dword ptr[eax+4*edx]
fxch st(1)
fmul dword ptr[eax+4*ebx]
fxch st(2)			;d32 d31 d21
fmul dword ptr[l64k]
fxch st(1)
fmul dword ptr[l64k]
fxch st(2)
fmul dword ptr[l64k]
fxch st(1)			;64kd32 64kd21 64kd31
fistp dword ptr[dx23]
fistp dword ptr[dx12]
fistp dword ptr[dx13]


;okreslenie kierunku trojkata [czy trzeba zmieniac delty]
push eax
mov eax,dx12
test byte ptr[flags+3],80h
jnz comp12
mov eax,dx23
cmp eax,dx13
jl swapd
jmp noswap
comp12:
cmp eax,dx13
jg swapd
noswap:
mov byte ptr[dir],0
jmp afterswap
swapd:
mov byte ptr[dir],1
afterswap:
pop eax


;liczenie 1/z i deltZ
fld dword ptr[l64k_256]
fld st
fld st
fld dword ptr[esi].v_vz
fld dword ptr[edi].v_vz
fld dword ptr[ebp].v_vz 	  ;z3 z2 z1 l64k256 l64k256 l64k256
fdivp st(3),st
fdivp st(3),st
fdivp st(3),st			;1/z3 1/z2 1/z1
fist dword ptr[z3]
fxch st(2)
fist dword ptr[z1]
fxch st(1)
fist dword ptr[z2]
fxch st(1)			;1/z1 1/z2 1/z3
fld st(2)
fld st(2)
fld st(2)
fsubp st(5),st
fxch st(2)
fsubp st(3),st
fxch st(1)
fsubp st(1),st
fxch st(1)			;z12 z23 z13
fmul dword ptr[eax+4*ebx]
fxch st(2)
fmul dword ptr[eax+4*edx]
fxch st(1)
fmul dword ptr[eax+4*ecx]
fxch st(1)			;dz13 dz23 dz12
fistp dword ptr[dz13]
fistp dword ptr[dz23]
fistp dword ptr[dz12]


;dzielnik dla stalych delt
;fld1
fld dword ptr[l64k]
fild dword ptr[dx13]
fild dword ptr[dz13]		 ;dz13 dx13 1
cmp ebx,0			;czy dx12==0
je std23
			;tu dla delt 1-2
fisub dword ptr[dz12]
fxch st(1)
fisub dword ptr[dx12]
fxch st(2)			;1 dz dx
fdivrp st(2),st
fxch st(1)			;1/(dx13-dx12) dz
fst dword ptr[dstale]
fmulp st(1),st
fistp dword ptr[dzstale]

jmp runproc
std23:			;tu liczymy dla delt 2-3
fisub dword ptr[dz23]
fxch st(1)
fisub dword ptr[dx23]
fxch st(2)			;1 dz dx
fdivrp st(2),st
fxch st(1)			;1/(dx13-dx23) dz
fst dword ptr[dstale]
fmulp st(1),st
fistp dword ptr[dzstale]


runproc:


;odpalenie procedur na trojkaty
mov esi,tr
mov edi,[esi].f_flags	;wez flagi

	;tymczasowo tylko 1 przebieg

and edi,0ffh			;index w tablicy procedur
mov eax,dword ptr trproc[4*edi] ;adres procedury
call eax			;odpal





koniectr:
popad
ret
endp


















;zmienne dla procek na trojkaty
temp dd 0
l64k dd 65536.0
l64k_256 dd 16777216.0


w1 dd 0      ;adresy wierzcholkow posortowane
w2 dd 0
w3 dd 0
y1 dd 0      ;integery wspolrzednych y
y2 dd 0
y3 dd 0
z1 dd 0      ;wartosci 1/z dla poszczegolnych wierzcholkow
z2 dd 0      ;24 bitowe
z3 dd 0
dx12 dd 0    ;delty x'ow 16.16
dx23 dd 0
dx13 dd 0
y12 dd 0     ;roznice y calkowite [adresy do fastdivtbl]
y23 dd 0
y13 dd 0
dz12 dd 0    ;delty 1/z 24 bitowe
dz23 dd 0
dz13 dd 0
dzstale dd 0  ;stala delta 1/z w linii poziomej,24 bitowa
dstale dd 0   ;wartosc do obliczania stalych przyrostow :
	      ;1/(dx12-dx13) lub 1/(dx23-dx13)
	      ;zaleznie od tego ktora jest wybrana
flags dd 0    ;flagi dla rysowania trojkata
licznik dd 0  ;licznik dla czesci trojkata
tr dd 0       ;adres struktury trojkata
fdt dd 0      ;adres fastdivtbl
scrx dd 0     ;szerokosc bufora w pikselach
bufor dd 0    ;adres bufora do rysowania
zbufor dd 0   ;adres zbufora
dir db 0      ;okresla kierunek trojkata - rozlozenie delt










;tablica adresow procedur na trojkaty
trproc: dd 256 dup(0)

;tablica adresow procedur inicjalizujacych
trinitproc: dd 256 dup(0)








code32 ends
end
