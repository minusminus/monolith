;SZABLON PROCKI NA TROJKAT
.386
code32 segment use32 public 'code' page
assume cs:code32,ds:code32,es:code32





;==================================================================
;OPIS DELT DLA TEXTUROWANIA
;delty liczone normalnie jako 8.16 potem:
;czesc ulamkowa laduje 4 bity wczesniej - shr reg,4
;dla tx - czesc calkowita zostaje tam gdzie byla
;dla ty - czesc calkowita 8 bitow w lewo shl reg,8
;puste miejsce w deltach, czyli tx-4bity ty-12 bitow wypelnimy jedynkami
;odpowiednio tx-f ty-fff - zeby w trakcie dodawania starszy bit mogl sie
;przeniesc na calkowita czesc
;z wartosciami w wierzcholkach robimy to samo, tylko nie wypelniamy pustych
;miejsc jedynkami
;==================================================================




;opis struktur
include scene.inc

;zmienne
include drawtr.inc



public trtex_
public trtexinit_


;we:
;esi - adres zbufora
;edi - adres bufora do rysowania
;edx - szerokosc bufora w pikselach*4
trtexinit_ proc
mov dword ptr[zbuf],esi
mov dword ptr[zbuf2],esi
mov dword ptr[buf],edi
mov dword ptr[scrY],edx
mov dword ptr[scrY2],edx
mov dword ptr[scrlen],edx
ret
endp



;procedura na trojkat
;we:
trtex_ proc
pushad

;laduj adres textury
mov esi,tr
mov eax,[esi].f_texaddy
mov dword ptr[texaddr],eax

;**************************************************************************
;tu liczenie innych potrzebnych delt dla trojkata
;tu dla linii 1-3
mov ebx,fdt	 ;'szybkie' dzielenie
mov esi,w1
mov edi,w3

fld dword ptr[edi].v_tx
fld dword ptr[edi].v_ty
fld dword ptr[edi].v_y2d
fsub dword ptr[esi].v_y2d	;y3-y1
fxch st(1)
fsub dword ptr[esi].v_ty	;ty3-ty1
fxch st(1)
fistp dword ptr[temp]
fxch st(1)
fsub dword ptr[esi].v_tx	;tx3-tx1
fxch st(1)			;dty dtx
mov ebp,temp			;offsecik do tablicy dzielenia
fmul dword ptr[ebx+4*ebp]
fxch st(1)
fmul dword ptr[ebx+4*ebp]
fxch st(1)
fmul dword ptr[l64k]
fxch st(1)
fmul dword ptr[l64k]
fxch st(1)			;dty13 dtx13
fistp dword ptr[dty13]
fistp dword ptr[dtx13]


;w zaleznosci czy dana czesc jest widoczna czy nie
test byte ptr[flags+3],80h	  ;bit 31 [czesc 12]
jz nocntpart12
mov esi,w1
mov edi,w2

fld dword ptr[edi].v_tx
fld dword ptr[edi].v_ty
fld dword ptr[edi].v_y2d
fsub dword ptr[esi].v_y2d	;y2-y1
fxch st(1)
fsub dword ptr[esi].v_ty	;ty2-ty1
fxch st(1)
fistp dword ptr[temp]
fxch st(1)
fsub dword ptr[esi].v_tx	;tx2-tx1
fxch st(1)			;dty dtx
mov ebp,temp			;offsecik do tablicy dzielenia
fmul dword ptr[ebx+4*ebp]
fxch st(1)
fmul dword ptr[ebx+4*ebp]
fxch st(1)
fmul dword ptr[l64k]
fxch st(1)
fmul dword ptr[l64k]
fxch st(1)			;dty12 dtx12
fistp dword ptr[dty12]
fistp dword ptr[dtx12]

nocntpart12:
test byte ptr[flags+3],40h	  ;bit 30 [czesc 23]
jz nocntpart23
mov esi,w2
mov edi,w3

fld dword ptr[edi].v_tx
fld dword ptr[edi].v_ty
fld dword ptr[edi].v_y2d
fsub dword ptr[esi].v_y2d	;y3-y2
fxch st(1)
fsub dword ptr[esi].v_ty	;ty3-ty2
fxch st(1)
fistp dword ptr[temp]
fxch st(1)
fsub dword ptr[esi].v_tx	;tx3-tx2
fxch st(1)			;dty dtx
mov ebp,temp			;offsecik do tablicy dzielenia
fmul dword ptr[ebx+4*ebp]
fxch st(1)
fmul dword ptr[ebx+4*ebp]
fxch st(1)
fmul dword ptr[l64k]
fxch st(1)
fmul dword ptr[l64k]
fxch st(1)			;dty23 dtx23
fistp dword ptr[dty23]
fistp dword ptr[dtx23]

nocntpart23:


;liczymy stale delty [powiny byc tu liczone wszystkie lacznie z Z]
mov esi,w1
mov edi,w2
mov ebp,w3
mov ebx,tr
test byte ptr[flags+3],80h	  ;bit 31 [czesc 12]
jz stalep23

;;fild dword ptr[ebx].f_d13
;fild dword ptr[dx13]
;;fisub dword ptr[ebx].f_d12
;fisub dword ptr[dx12]
;fld dword ptr[l64k]
;fdivrp st(1),st		 ;1/(d12-d13)
;fld dword ptr[l64k]
fld1
fmul dword ptr[dstale]
fild dword ptr[dtx13]
fild dword ptr[dty13]
fisub dword ptr[dty12]		 ;dty12-dty13
fxch st(1)
fisub dword ptr[dtx12]		 ;dtx12-dtx13
fxch st(1)
fld st(2)
fmulp st(2),st
fmulp st(2),st			;staledty staledtx
fistp dword ptr[staledtx]
fistp dword ptr[staledty]

jmp gopart12
stalep23:

;;fild dword ptr[ebx].f_d13
;fild dword ptr[dx13]
;;fisub dword ptr[ebx].f_d23
;fisub dword ptr[dx23]
;fld dword ptr[l64k]
;fdivrp st(1),st		 ;1/(d23-d13)
;fld dword ptr[l64k]
fld1
fmul dword ptr[dstale]
fild dword ptr[dtx13]
fild dword ptr[dty13]
fisub dword ptr[dty23]		 ;dty23-dty13
fxch st(1)
fisub dword ptr[dtx23]		 ;dtx23-dtx13
fxch st(1)
fld st(2)
fmulp st(2),st
fmulp st(2),st			;staledty staledtx
fistp dword ptr[staledtx]
fistp dword ptr[staledty]

gopart12:

;zmiana delt
;DOPIERO PO PRZELICZENIU STALYCH DELT W TROJKACIE
mov eax,dtx13		;1-3
mov edx,dtx13
shr edx,4
and edx,000000fffh	;odpowiednie zamaskowanie
and eax,000ff0000h
or eax,edx
or eax,00000f000h	;wypelnienie pustego miejsca
mov dtx13,eax

mov eax,dty13
mov edx,dty13
shl eax,8
shr edx,4
and edx,000000fffh
and eax,0ff000000h
or eax,edx
or eax,000fff000h
mov dty13,eax

mov eax,dtx12		;1-2
mov edx,dtx12
shr edx,4
and edx,000000fffh	;odpowiednie zamaskowanie
and eax,000ff0000h
or eax,edx
or eax,00000f000h	;wypelnienie pustego miejsca
mov dtx12,eax

mov eax,dty12
mov edx,dty12
shl eax,8
shr edx,4
and edx,000000fffh
and eax,0ff000000h
or eax,edx
or eax,000fff000h
mov dty12,eax

mov eax,dtx23		;2-3
mov edx,dtx23
shr edx,4
and edx,000000fffh	;odpowiednie zamaskowanie
and eax,000ff0000h
or eax,edx
or eax,00000f000h	;wypelnienie pustego miejsca
mov dtx23,eax

mov eax,dty23
mov edx,dty23
shl eax,8
shr edx,4
and edx,000000fffh
and eax,0ff000000h
or eax,edx
or eax,000fff000h
mov dty23,eax

mov eax,dword ptr[staledtx]	      ;stale
mov edx,dword ptr[staledtx]
shr edx,4
and edx,000000fffh	;odpowiednie zamaskowanie
and eax,000ff0000h
or eax,edx
or eax,00000f000h	;wypelnienie pustego miejsca
mov dword ptr[staledtx],eax
mov eax,dword ptr[staledty]
mov edx,dword ptr[staledty]
shl eax,8
shr edx,4
and edx,000000fffh
and eax,0ff000000h
or eax,edx
or eax,000fff000h
mov dword ptr[staledty],eax


;**************************************************************************
;ladowanie delt
;pamietac o deltach dodatkowych dla trojkata
;mov ebx,tr
;mov eax,[ebx].f_d12
;test byte ptr[flags+3],80h
;jnz comp12
;mov eax,[ebx].f_d23
;cmp eax,[ebx].f_d13
;jl swapd
;jmp noswap
;comp12:
;cmp eax,[ebx].f_d13
;jg swapd
cmp byte ptr[dir],0
jne swapd
;tu mniejsza (normalnie trojkat)
noswap:
;mov eax,[ebx].f_d12
mov eax,dx12
mov dl1,eax
;mov ecx,[ebx].f_d23
mov ecx,dx23
;mov edx,[ebx].f_d13
mov edx,dx13
mov dl2,ecx
mov dp1,edx
mov dp2,edx
;mov eax,[ebx].f_dz12
mov eax,dz12
;mov ecx,[ebx].f_dz23
mov ecx,dz23
mov dz1,eax
mov dz2,ecx
mov eax,dtx12
mov ecx,dty12
mov dtx1,eax
mov dty1,ecx
mov eax,dtx23
mov ecx,dty23
mov dtx2,eax
mov dty2,ecx
;mov dir,0
jmp ladujZ
swapd:
;zmaina delt (rysowanie odwrotnego trojkata)
;mov eax,[ebx].f_d12
mov eax,dx12
mov dp1,eax
;mov ecx,[ebx].f_d13
mov ecx,dx13
;mov edx,[ebx].f_d23
mov edx,dx23
mov dp2,edx
mov dl1,ecx
mov dl2,ecx
;mov eax,[ebx].f_dz13
mov eax,dz13
mov dz1,eax
mov dz2,eax
mov eax,dtx13
mov ecx,dty13
mov dtx1,eax
mov dty1,ecx
mov dtx2,eax
mov dty2,ecx
;mov dir,1
ladujZ:
;stale deltaZ w linii poziomej
;inne stale delty tez ladowane tutaj
;mov eax,[ebx].f_dzx
;mov dword ptr[stalez],eax	      ;selfmod (1 cykl zamiast 2)
mov eax,dzstale
mov dword ptr[stalez],eax







;**************************************************************************
;czesc 1->2
mov esi,w1
mov edi,w2
test byte ptr[flags+3],80h	  ;bit 31 [czesc 12]
jz nopart12

;rysowanie 1->2
;inicjalizacja rejestrow i zmiennych przed rysowaniem danej czesci
mov eax,dl1
mov edx,dp1
mov deltal,eax
mov deltap,edx
mov eax,dz1
mov deltaz,eax
mov eax,dtx1
mov edx,dty1
mov deltatx,eax
mov deltaty,edx
fld dword ptr[esi].v_x2d
fmul dword ptr[l64k]
fistp dword ptr[temp]
mov ebx,temp		;xl
mov ecx,temp		;xp

;fld dword ptr[edi].v_y2d
;fld dword ptr[esi].v_y2d
;fsub st(1),st	 ;y2-y1
;fmul dword ptr[l320]	;y1*XSCREEN
;fxch st(1)
;fistp dword ptr[temp]
;mov ebp,temp	       ;licznik
;fistp dword ptr[temp]
;mov edi,temp	       ;adres w buforze
mov edi,y1
mov ebp,y12
imul edi,12345678h	;adrs w buforze
     scrY = $-4

fld dword ptr[esi].v_tx
fld dword ptr[esi].v_ty
fmul dword ptr[l64k]
fxch st(1)
fmul dword ptr[l64k]
fxch st(1)
fistp dword ptr[temp]		;ty 8.16
mov edx,temp
fistp dword ptr[temp]		;tx 8.16
mov eax,temp

push eax			;zamiana wspolzednych poczatkowych
mov eax,edx			;textury
shl edx,8
shr eax,4
and edx,0ff000000h
and eax,000000fffh
or edx,eax
pop eax
push edx
mov edx,eax
shr edx,4
and eax,000ff0000h
and edx,000000fffh
or eax,edx
pop edx


;fld dword ptr[l64k]
;fdiv dword ptr[esi].v_vz	 ;1/z
;fistp dword ptr[temp]
;mov esi,temp
;shl esi,8
mov esi,z1
jmp goline		;nie trzeba stawiac pktu w pierwszym wierzcholku


;***********************************************************************
;inner loop
;edi - koniec linii w buforze
;ecx - dlugosc linii zanegowana
;esi - wartosc zbufora
;eax - tx 8.16
;edx - ty 8.24
;ebp - adres w texturze dla pierwszego pktu
innerloop:
cmp esi,[edi+4*ecx+12345678h]
    zbuf = $-4
jbe notput
mov ebx,[4*ebp+12345678h]		;wez texel
    texaddr = $-4
mov [edi+4*ecx+12345678h],esi		;wstaw do zbufora
    zbuf2 = $-4
mov [edi+4*ecx+12345678h],ebx		;postaw pkt na ekranie
    buf = $-4
notput:
lea ebp,[edx+eax]			;adres w texturze
shr ebp,16
add esi,12345678h			;nast Z w linii
    stalez = $-4
add eax,12345678h			;+ stale dtx
    staledtx = $-4
add edx,12345678h			;+ stale dty
    staledty = $-4
and eax,000ff0fffh			;\wspolrzedne w texturze
and edx,0ff000fffh			;/
inc ecx
js innerloop

;***********************************************************************

pop esi edi ebp ebx ecx edx eax
goline:
add edi,12345678h	;dodaj dlugosc linii w bajtach
    scrlen = $-4
add esi,deltaz
add ecx,deltap
add ebx,deltal
add eax,deltatx
add edx,deltaty
dec ebp
jnz poczateklinii
jmp koniecczesci

poczateklinii:
and eax,000ff0fffh
and edx,0ff000fffh
push eax edx ecx ebx ebp edi
;and eax,000ff0fffh
;and edx,0ff000fffh
sar ebx,16
push esi
sar ecx,16
lea ebp,[edx+eax]		;adres w texturze
lea edi,[edi+4*ecx]		;adres konca linii w buforze
sub ecx,ebx			;dlugosc linii
neg ecx
shr ebp,16
jmp innerloop

koniecczesci:






;koniec rysowania danej czesci trojkata - zachowanie wartosci itp
dec dword ptr[licznik]
jz koniec
cmp dir,0
je do23
xchg ebx,ecx		;to tylko gdy odwrotnie mamy trojkat
mov savez,esi
mov savetx,eax
mov savety,edx
jmp do23
;jmp koniec

;do czesci 2->3
nopart12:
test byte ptr[flags+3],40h	  ;bit 30 [czesc 23]
jz koniec
mov ebp,w1
fld dword ptr[ebp].v_x2d
fmul dword ptr[l64k]
fistp dword ptr[temp]
mov ecx,temp		;poczatkowe xp jak nie bylo czesci 1->2
;fld dword ptr[l64k]
;fdiv dword ptr[ebp].v_vz
;fistp dword ptr[savez]
;shl dword ptr[savez],8
push esi
mov esi,z1
mov savez,esi
pop esi
fld dword ptr[ebp].v_tx 	;to jest liczone dla przypadku gdy nie ma
fld dword ptr[ebp].v_ty 	;1->2 i trojkat jest odwrotnie
fmul dword ptr[l64k]	    ;dlatego mozna to zrzucic tylko do save'ow
fxch st(1)			;i z pierwszego wierzcholka
fmul dword ptr[l64k]
fxch st(1)
fistp dword ptr[savety]
fistp dword ptr[savetx]

mov eax,savety		;zamiana poczatkowych wspolrzednych
mov edx,savety
shl edx,8
shr eax,4
and edx,0ff000000h
and eax,000000fffh
or edx,eax
mov savety,edx
mov edx,savetx
mov eax,savetx
shr edx,4
and eax,000ff0000h
and edx,000000fffh
or eax,edx
mov savetx,eax



;**************************************************************************
do23:		;normalna juz czesc 23
mov eax,dl2
mov edx,dp2
mov deltal,eax
mov deltap,edx
mov eax,dz2
mov deltaz,eax
mov eax,dtx2
mov edx,dty2
mov deltatx,eax
mov deltaty,edx
mov esi,w2
mov edi,w3
fld dword ptr[esi].v_x2d
fmul dword ptr[l64k]
fistp dword ptr[temp]
mov ebx,temp	      ;xl
;fld dword ptr[edi].v_y2d
;fld dword ptr[esi].v_y2d
;fsub st(1),st		 ;y3-y2
;fmul dword ptr[l320]	 ;y2*XSCREEN
;fxch st(1)
;fistp dword ptr[temp]
;mov ebp,temp	       ;licznik
;fistp dword ptr[temp]
;mov edi,temp	       ;w buforze
mov ebp,y23
mov edi,y2
imul edi,12345678h	;adres w buforze
     scrY2 = $-4

fld dword ptr[esi].v_tx  ;tx
fld dword ptr[esi].v_ty  ;ty
fmul dword ptr[l64k]
fxch st(1)
fmul dword ptr[l64k]
fxch st(1)
fistp dword ptr[temp]
mov edx,temp		;ty
fistp dword ptr[temp]
mov eax,temp		;tx

push eax			;zamiana wspolzednych poczatkowych
mov eax,edx			;textury
shl edx,8
shr eax,4
and edx,0ff000000h
and eax,000000fffh
or edx,eax
pop eax
push edx
mov edx,eax
shr edx,4
and eax,000ff0000h
and edx,000000fffh
or eax,edx
pop edx



;fld dword ptr[l64k]
;fdiv dword ptr[esi].v_vz	 ;1/z
;fistp dword ptr[temp]
;mov esi,temp
;shl esi,8
mov esi,z2
cmp dir,0
je poczateklinii	;tu juz trzeba narysowac pierwsza linie
xchg ebx,ecx
mov esi,savez
mov eax,savetx
mov edx,savety
jmp poczateklinii



koniec:
popad
ret
endp


l255 dd 255.0
dl1 dd 0
dl2 dd 0
dp1 dd 0
dp2 dd 0
dz1 dd 0
dz2 dd 0
dtx1 dd 0
dtx2 dd 0
dty1 dd 0
dty2 dd 0
dtx12 dd 0
dty12 dd 0
dtx13 dd 0
dty13 dd 0
dtx23 dd 0
dty23 dd 0
deltal dd 0
deltap dd 0
deltaz dd 0
deltatx dd 0
deltaty dd 0
savez dd 0
savetx dd 0
savety dd 0
temp dd 0

code32 ends
end